#include "LedControl.h"
#define MODULES_X 5
#define MODULES_Y 2
#define MODULES_COUNT MODULES_X*MODULES_Y
#define PIXELS_X MODULES_X*8
#define PIXELS_Y MODULES_Y*8

bool FrameBuffer[PIXELS_Y][PIXELS_X];
LedControl lc = LedControl(12, 11, 10, MODULES_COUNT);

byte character[200][5];

void clearBuffer() {
  for (int i = 0; i < PIXELS_Y; i++)
    for (int j = 0; j < PIXELS_X; j++)
      FrameBuffer[i][j] = false;
}

void setup() {
  for (int i = 0; i < MODULES_COUNT; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  clearBuffer();
}

byte boolToByte(int startY, int startX) {
  byte b = 0;
  for (int i = 0; i < 8; i++)
    b |= FrameBuffer[startY][startX + i] << (7 - i);
  return b;
}

void redisplay() {
  int module;
  for (int i = 0; i < PIXELS_Y; i++) {
    for (int j = 0; j < PIXELS_X; j += 8) {
      module = (j / 8) + (5 * (i / 8));
      lc.setRow(module, i % 8, boolToByte(i, j));
    }
  }
}

void draw5x4(int posY, int posX, char c) {

}

void loop() {
  // put your main code here, to run repeatedly:

}
