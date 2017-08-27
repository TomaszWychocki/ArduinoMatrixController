#include <LEDMatrixDriver.hpp>
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
  lmd.setIntensity(2);   // 0 = low, 10 = high
  clearBuffer();
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

void draw5x4(int posY, int posX, char c) {

}

int dx = 1, dy = -1;
int posx = 6, posy = 10;

void loop() {
  FrameBuffer[posy][posx] = false;

  posy+=dy;
  posx+=dx;
  FrameBuffer[posy][posx] = true;

  if(posy <= 0) dy = 1;
  if(posy >= 15) dy = -1;
  if(posx <= 0) dx = 1;
  if(posx >= 39) dx = -1;

  redisplay();
  delay(10);
}
