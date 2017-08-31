#include <LEDMatrixDriver.hpp>
#include <EEPROM.h>
#include "font.h"
#define MODULES_X 5
#define MODULES_Y 2
#define MODULES_COUNT MODULES_X*MODULES_Y
#define PIXELS_X MODULES_X*8
#define PIXELS_Y MODULES_Y*8

void displayText(String);
/*
  EEPROM:
  0 - LED Intensity
  1 - alarm 1 hour
  2 - alarm 1 minute
  3 - alarm 1 status
*/

bool FrameBuffer[PIXELS_Y][PIXELS_X];
LEDMatrixDriver lmd(MODULES_COUNT, 15); //CS MOSI=DIN
long int lastSecond = 0;
bool alarmOn = false;

#include "wifi.h"

void clearBuffer() {
  for (int i = 0; i < PIXELS_Y; i++)
    for (int j = 0; j < PIXELS_X; j++)
      FrameBuffer[i][j] = false;
}

void setup() {
  EEPROM.begin(512);
  lmd.setEnabled(true);
  lmd.setIntensity(EEPROM.read(0));   // 0 = low, 10 = high
  clearBuffer();
  draw8x16(0, 0, g / 10);
  draw8x16(0, 9, g % 10);
  draw8x16(0, 23, m / 10);
  draw8x16(0, 32, m % 10);
  redisplay();

  //displayText("Tomasz Wychocki");

  Serial.begin(115200);
  connectWiFi();

  server.on("/", handleRoot);
  server.begin();
  
  getNTPTime();
}

void redisplay() {
  int x = 40, y = 0;

  for (int i = 0; i < PIXELS_Y / 2; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      lmd.setPixel(x++, y, FrameBuffer[i][j]);
      if (x >= 80) {
        x = 40;
        y++;
      }
    }
  }

  x = 0; y = 0;

  for (int i = PIXELS_Y / 2; i < PIXELS_Y; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      lmd.setPixel(x++, y, FrameBuffer[i][j]);
      if (x >= 40) {
        x = 0;
        y++;
      }
    }
  }

  lmd.display();
}

void draw8x16(int posY, int posX, int number) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      FrameBuffer[posY + i][posX + j] = font8x16[number][i] & (1 << (7 - j));
    }
  }
}

void displayText(String text) {
  bool **a;
  a = (bool **) malloc(7 * sizeof(bool *));
  for (int i = 0; i < 7; i++)
    a[i] = (bool *) malloc(6 * text.length() * sizeof(bool));

  clearBuffer();
  int posx = 0;

  for (int c = 0; c < text.length(); c++) {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 5; j++) {
        a[i][j + posx] = font5x7[text[c] - 32][i] & (1 << (4 - j));
      }
    }
    posx += 8;
  }

  posx = 0;

  while (posx < 40 + (6 * text.length())) {
    if (posx < 6 * text.length()) {
      for (int i = 0; i < 7; i++) {
        FrameBuffer[4 + i][39] = a[i][posx];
      }
    }
    redisplay();
    posx++;
    delay(100);
    for (int i = 0; i < 7; i++) {
      for (int j = 1; j < 40; j++) {
        FrameBuffer[i][j - 1] = FrameBuffer[i][j];
      }
    }
  }

  for (int i = 0; i < 7; i++)
    free(a[i]);
  free(a);
  clearBuffer();
}

void checkAlarm() {
  if(g == EEPROM.read(1) && m == EEPROM.read(2) && s <= 5 && EEPROM.read(3) == 1)
    alarmOn = true;
}

void loop() {
  if (millis() - last >= 300000) {
    getNTPTime();
  }

  if (millis() - lastSecond >= 1000) {
    s++;
    lastSecond = millis();
  }
  if (s == 60) {
    s = 0;
    m++;
  }
  if (m == 60) {
    m = 0;
    g++;
  }
  if (g == 24) {
    g = 0;
  }

  draw8x16(0, 0, g / 10);
  draw8x16(0, 9, g % 10);
  draw8x16(0, 23, m / 10);
  draw8x16(0, 32, m % 10);

  FrameBuffer[5][20] = true; FrameBuffer[6][20] = true; FrameBuffer[5][19] = true; FrameBuffer[6][19] = true;
  FrameBuffer[9][20] = true; FrameBuffer[10][20] = true; FrameBuffer[9][19] = true; FrameBuffer[10][19] = true;

  redisplay();

  //----------------WEBSERVER-------------------
  server.handleClient();

  delay(100);
}
