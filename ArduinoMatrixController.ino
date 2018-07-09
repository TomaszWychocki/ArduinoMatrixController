#include <MD_MAX72xx.h>
#include <SPI.h>
#include "font.h"

#define MODULES_X 5
#define MODULES_Y 2
#define MODULES_COUNT MODULES_X*MODULES_Y
#define PIXELS_X MODULES_X*8
#define PIXELS_Y MODULES_Y*8
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 10
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool FrameBuffer[PIXELS_Y][PIXELS_X];
long int lastSecond = 0;
int g = 0, m = 0, s = 40;

void clearBuffer()
{
  for (int i = 0; i < PIXELS_Y; i++)
    for (int j = 0; j < PIXELS_X; j++)
      FrameBuffer[i][j] = false;
}

void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void setup() {
  clearBuffer();
  mx.begin();
  resetMatrix();  
  draw8x16(0, 0, g / 10);
  draw8x16(0, 9, g % 10);
  draw8x16(0, 23, m / 10);
  draw8x16(0, 32, m % 10);
  redisplay();
}

void redisplay() {
  //mx.clear();
  mx.update(MD_MAX72XX::OFF);

  for (int i = 0; i < PIXELS_Y / 2; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      mx.setPoint(i, PIXELS_X - j - 1, FrameBuffer[i][j]);
    }
  }

  for (int i = PIXELS_Y / 2; i < PIXELS_Y; i++) {
    for (int j = 0; j < PIXELS_X; j++) {
      mx.setPoint(i - (PIXELS_Y / 2), PIXELS_X - j + 39, FrameBuffer[i][j]);
    }
  }
  
  mx.update(MD_MAX72XX::ON);
}

void draw8x16(int posY, int posX, int number) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      FrameBuffer[posY + i][posX + j] = font8x16[number][i] & (1 << (7 - j));
    }
  }
}

void displayText(String text, int speed) {
  bool **a;
  a = (bool **) malloc(7 * sizeof(bool *));
  for (int i = 0; i < 7; i++)
    a[i] = (bool *) malloc(7 * text.length() * sizeof(bool));

  for (int i = 0; i < 7; i++)
    for (int j = 0; j < (7 * text.length()); j++)
      a[i][j] = false;

  clearBuffer();
  int posx = 0;

  for (int c = 0; c < text.length(); c++) {
    int t = text[c] - 32;
    if (t >= 65) t--;
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 5; j++) {
        a[i][j + posx] = font5x7[t][i] & (1 << (4 - j));
      }
    }
    posx += 6;
  }

  posx = 0;

  while (posx < (39 + (6 * text.length()))) {
    if (posx < 6 * text.length()) {
      for (int i = 0; i < 7; i++) {
        FrameBuffer[4 + i][39] = a[i][posx];
      }
    }
    redisplay();
    posx++;
    delay(speed);
    for (int i = 0; i < 7; i++) {
      for (int j = 1; j < 40; j++) {
        FrameBuffer[4 + i][j - 1] = FrameBuffer[4 + i][j];
      }
    }
  }

  for (int i = 0; i < 7; i++)
    free(a[i]);
  free(a);
  clearBuffer();
}

void loop() {
  if (millis() - lastSecond >= 1000) {
    s++;
    lastSecond = millis();

    redisplay();
    clearBuffer();
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
}

