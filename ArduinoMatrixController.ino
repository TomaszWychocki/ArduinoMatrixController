#include <LEDMatrixDriver.hpp>
#include "font.h"
#include "wifi.h"
#define MODULES_X 5
#define MODULES_Y 2
#define MODULES_COUNT MODULES_X*MODULES_Y
#define PIXELS_X MODULES_X*8
#define PIXELS_Y MODULES_Y*8

bool FrameBuffer[PIXELS_Y][PIXELS_X];
LEDMatrixDriver lmd(MODULES_COUNT, 9); //CS MOSI=DIN

byte character[200][5];

void clearBuffer() {
  for (int i = 0; i < PIXELS_Y; i++)
    for (int j = 0; j < PIXELS_X; j++)
      FrameBuffer[i][j] = false;
}

void setup() {
  lmd.setEnabled(true);
  lmd.setIntensity(0);   // 0 = low, 10 = high
  clearBuffer();

  Serial.begin(115200);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network"); 
  Udp.begin(localPort);

  getNTPTime();
}

void redisplay() {
  int x=40, y=0;
  
  for (int i = 0; i < PIXELS_Y/2; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      lmd.setPixel(x++,y,FrameBuffer[i][j]);
      if(x >= 80) {
        x = 40;
        y++;  
      }
    }
  }

  x=0; y=0;
  
  for (int i = PIXELS_Y/2; i < PIXELS_Y; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      lmd.setPixel(x++,y,FrameBuffer[i][j]);
      if(x >= 40) {
        x = 0;
        y++;  
      }
    }
  }

  lmd.display();
}

void draw8x16(int posY, int posX, int number) {
  for(int i=0; i<16; i++) {
    for(int j=0; j<8; j++) {
        FrameBuffer[posY+i][posX+j] = font8x16[number][i] & (1 << (7-j));
    }  
  }
}

void loop() {
  if(millis()-last>=3600000) { getNTPTime(); }
  
  draw8x16(0,0,g/10);
  draw8x16(0,9,g%10);
  draw8x16(0,23,m/10);
  draw8x16(0,32,m%10);

  FrameBuffer[5][20] = true; FrameBuffer[6][20] = true; FrameBuffer[5][19] = true; FrameBuffer[6][19] = true;
  FrameBuffer[9][20] = true; FrameBuffer[10][20] = true; FrameBuffer[9][19] = true; FrameBuffer[10][19] = true;
  
  redisplay();
  delay(1000);
}
