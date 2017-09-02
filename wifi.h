#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>

char ssid[] = "Nigdy wiecej darmowego Wi-Fi";
char pass[] = "Hulajnoga1999";
unsigned int localPort = 2390;
IPAddress timeServerIP;
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
WiFiUDP udp;
ESP8266WebServer server(80);

int g = 0, m = 0, s = 0;
long int last = 0;

char *getHTMLContent() {
  String html = "";
  html +=
    "<!DOCTYPE HTML>"
    "<html>"
    "<head>"
    "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
    "<meta charset=\"utf-8\">"
    "<title>Sterownik LED</title>"
    "</head>"
    "<body>"
    "<h1>Sterownik zegara LED</h1>"
    "<h2>Godzina: ";
  if(g < 10) html += "0";
    html += g;
  html += ":";
  if(m < 10) html += "0";
    html += m;
  html += ":";
  if(s < 10) html += "0";
    html += s;
  html +=
    "</h2><FORM action=\"/\" method=\"post\">"
    "<P>"
    "Jasność: ";
  html += EEPROM.read(0);
  html +=   
    "<br><input type=\"range\" name=\"LEDIntensity\" min=\"0\" max=\"10\" value=\"";
  html += EEPROM.read(0);
  html +=
    "\"><input type=\"submit\" value=\"Zmień jasnosć\">"
    "</P>"
    "</FORM>"
      "<FORM action=\"/\" method=\"post\">"
    "<P><br><br>"
    "Alarm 1: ";
  if(EEPROM.read(1) < 10) html += "0";
  html += EEPROM.read(1);
  html += ":";
  if(EEPROM.read(2) < 10) html += "0";
  html += EEPROM.read(2);
  html +=   
    "<br><input type=\"time\" name=\"alarm1Time\">"
    "<input type=\"submit\" value=\"Ustaw alarm #1\"><br>";
  if(EEPROM.read(3) == 1)
    html += 
      "<input type=\"radio\" name=\"alarm1Status\" value=\"on\" checked> Włącz"
      "<input type=\"radio\" name=\"alarm1Status\" value=\"off\"> Wyłącz";
  else
    html += 
      "<input type=\"radio\" name=\"alarm1Status\" value=\"on\"> Włącz"
      "<input type=\"radio\" name=\"alarm1Status\" value=\"off\" checked> Wyłącz";
  html += 
    "</P>"
    "</FORM>"
    "</body>"
    "</html>";

  html += "\0";
  char *arr = (char*) malloc((html.length() + 1) * sizeof(char));
  html.toCharArray(arr, html.length() + 1);
  return arr;
}

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  displayText("Connecting to " + String(ssid), 15);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  displayText("WiFi connected", 15);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  displayText("IP address: " + WiFi.localIP().toString(), 15);

  Serial.println("Starting UDP");
  displayText("Starting UDP", 15);
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
  displayText("Local port: " + String(udp.localPort()), 15);
}

unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void getNTPTime() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();

  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP);

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);

    g = (((epoch  % 86400L) / 3600) + 2) % 24;
    m = (epoch  % 3600) / 60;
    s = epoch % 60;

    Serial.print("The UTC time is ");
    Serial.print(g);
    Serial.print(':');
    if (m < 10) {
      Serial.print('0');
    }
    Serial.print(m);
    Serial.print(':');
    if (s < 10) {
      Serial.print('0');
    }
    Serial.println(s);
  }

  last = millis();
}

void handleRoot() {
  char *content;
  
  if (server.hasArg("LEDIntensity")) {
    String LEDIntensity = server.arg("LEDIntensity");
    Serial.println(LEDIntensity);
    int ledI = LEDIntensity.toInt();
    EEPROM.write(0, ledI);
    EEPROM.commit(); 
    lmd.setIntensity(EEPROM.read(0));
    content = getHTMLContent();
    server.send(200, "text/html", content);
  }
  else if(server.hasArg("alarm1Time")) {
    String alarm1Time = server.arg("alarm1Time");
    int alarmHour = alarm1Time.substring(0,2).toInt();
    int alarmMinute = alarm1Time.substring(3,5).toInt();
    Serial.print(alarmHour);
    Serial.print(":");
    Serial.println(alarmMinute);
    EEPROM.write(1, alarmHour);
    EEPROM.commit(); 
    EEPROM.write(2, alarmMinute);
    EEPROM.commit();

    String alarm1Status = server.arg("alarm1Status");
    if(alarm1Status.equals("on"))
      EEPROM.write(3, 1);
    else
      EEPROM.write(3, 0);
    EEPROM.commit();
    
    content = getHTMLContent();
    server.send(200, "text/html", content);
  }
  else {
    content = getHTMLContent();
    server.send(200, "text/html", content);
  }

  free(content);
}
