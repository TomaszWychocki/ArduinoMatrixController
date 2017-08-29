#include "WiFiEspUdp.h"

#include "SoftwareSerial.h"
SoftwareSerial ESP(2,3); // RX, TX

char timeServer[] = "time.nist.gov";
unsigned int localPort = 2390;
const int NTP_PACKET_SIZE = 48;
const int UDP_TIMEOUT = 2000;
byte packetBuffer[NTP_PACKET_SIZE];

WiFiEspUDP Udp;

int g = 0, m = 0, s = 0;
long int last = 0;

boolean wyslij(char * Komenda_AT, char *Odpowiedz_AT, int czas_czekania) {
  ESP.println(Komenda_AT);
  delay(czas_czekania);
  while (ESP.available() > 0) {
    if (ESP.find(Odpowiedz_AT)) {
      return 1;
    }
  }
  return 0;
}

void connectWiFi() {
  while (!wyslij("AT", "OK", 100)) {
    Serial.println("Błąd komunikacji z modułem");
    delay(1000);
  }
  Serial.println("Komunikacja OK");

  if (wyslij("AT+CWMODE=1", "OK", 500))
    Serial.println("CWMODE - OK!");
  if (wyslij("AT+CIPMODE=0", "OK", 500))
    Serial.println("CIPMODE - OK!");
  if (wyslij("AT+CIPMUX=1", "OK", 500))
    Serial.println("CIPMUX - OK!");

  if (wyslij("AT+CWJAP=\"Nigdy wiecej darmowego Wi-Fi\",\"Hulajnoga1999\"", "OK", 8000))
    Serial.println("Polaczono z siecia!");
  else
    Serial.println("Błąd łączenia z siecią!");

  if (wyslij("AT+CIPSERVER=1,80", "OK", 5000))
    Serial.println("Uruchomiono serwer :)");

  ESP.println("AT+CIFSR");
  Serial.println(ESP.readString());
  delay(200);  
}

void sendNTPpacket(char *ntpSrv) {
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
  Udp.beginPacket(ntpSrv, 123); //NTP requests are to port 123

  Udp.write(packetBuffer, NTP_PACKET_SIZE);

  Udp.endPacket();
}

void getNTPTime() {
  sendNTPpacket(timeServer);
  
  unsigned long startMs = millis();
  while (!Udp.available() && (millis() - startMs) < UDP_TIMEOUT) {}

  Serial.println(Udp.parsePacket());
  if (Udp.parsePacket()) {
    Serial.println("packet received");

    Udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;

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
