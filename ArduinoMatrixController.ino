#include <MD_MAX72xx.h>
#include <avr/pgmspace.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include "font.h"

#define MODULES_X 5
#define MODULES_Y 2
#define MODULES_COUNT MODULES_X*MODULES_Y
#define PIXELS_X MODULES_X*8
#define PIXELS_Y MODULES_Y*8
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 10
#define CLK_PIN   7  // or SCK
#define DATA_PIN  6  // or MOSI
#define CS_PIN    5  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool FrameBuffer[PIXELS_Y][PIXELS_X];
uint8_t g = 23, m = 11, s = 55;
long int lastSecond = 0;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
unsigned int localPort = 8888;
char timeServer[] = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
EthernetUDP Udp;

void getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) 
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) 
    {
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      unsigned long epoch = secsSince1900 - 2208988800UL + (0 * 3600);

      g = (((epoch  % 86400L) / 3600) + 2) % 24;
      m = (epoch  % 3600) / 60;
      s = epoch % 60;
    }
  }
  return 0; // return 0 if unable to get the time
}

void sendNTPpacket(char* address) {
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
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void clearBuffer()
{
  for (size_t i = 0; i < PIXELS_Y; i++)
    for (size_t j = 0; j < PIXELS_X; j++)
      FrameBuffer[i][j] = false;
}

void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void redisplay()
{
  //mx.clear();
  mx.update(MD_MAX72XX::OFF);

  for (size_t i = 0; i < PIXELS_Y / 2; i++)
  {
    for (size_t j = 0; j < PIXELS_X; j++)
    {
      mx.setPoint(i, PIXELS_X - j - 1, FrameBuffer[i][j]);
    }
  }

  for (size_t i = PIXELS_Y / 2; i < PIXELS_Y; i++)
  {
    for (size_t j = 0; j < PIXELS_X; j++)
    {
      mx.setPoint(i - (PIXELS_Y / 2), PIXELS_X - j + 39, FrameBuffer[i][j]);
    }
  }

  mx.update(MD_MAX72XX::ON);

  for (size_t i = 0; i < PIXELS_Y; i++)
  {
    for (size_t j = 0; j < PIXELS_X; j++)
    {
      if(FrameBuffer[i][j])
        Serial.print("X");
      else
        Serial.print("_");
    }
    Serial.println();
  }
  Serial.println("\n\n\n");
}

void draw8x16(size_t posY, size_t posX, uint8_t number)
{
  if(number > 9 || number < 0) number = 0;
  
  for (size_t i = 0; i < 16; i++)
  {
    for (size_t j = 0; j < 8; j++)
    {
      FrameBuffer[posY + i][posX + j] = pgm_read_byte(&(font8x16[number][i])) & (1 << (7 - j));
    }
  }
}

void setup()
{
  Serial.begin(57600);
  clearBuffer();
  mx.begin();
  resetMatrix();

  Ethernet.begin(mac);
  Udp.begin(localPort);
  getNtpTime();
}

void loop()
{
  if (millis() - lastSecond >= 1000) {
    s++;
    lastSecond = millis();

    draw8x16(0, 0, (g / 10) % 10);
    draw8x16(0, 9, g % 10);
    draw8x16(0, 23, (m / 10) % 10);
    draw8x16(0, 32, m % 10);
  
    FrameBuffer[5][20] = true; FrameBuffer[6][20] = true; FrameBuffer[5][19] = true; FrameBuffer[6][19] = true;
    FrameBuffer[9][20] = true; FrameBuffer[10][20] = true; FrameBuffer[9][19] = true; FrameBuffer[10][19] = true;
  
    redisplay();
    clearBuffer();
  }
  
  if (s == 60) {
    s = 0;
    m++;
    getNtpTime();
  }
  
  if (m == 60) {
    m = 0;
    g++;
  }
  
  if (g == 24) {
    g = 0;
  }
}

