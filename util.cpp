#include "gamecore.h"
#include "assets.h"

bool Collision(
  const int x1, const char y1, const byte w1, const byte h1, 
  const int x2, const char y2, const byte w2, const byte h2
) {
  if(x1 + w1 < x2 || x1 > x2 + w2) { return false; }
  if(y1 + h1 < y2 || y1 > y2 + h2) { return false; }
  return true;
}

int Clamp(const int value, const int min, const int max) {
  if(value < min) { return min; }
  if(value > max) { return max; }
  return value;
}

void DrawWave(GameCore& core, const int beginX, const unsigned long frameCount) {
  const byte w = bitmapWave[0];
  const char d = beginX % w;
  const char x = (w * 2 + d - (char)(frameCount / 20 % 4) * (w / 4)) % w;
  core.drawBitmap(x - w, 0, bitmapWave, 1);
  core.drawBitmap(x    , 0, bitmapWave, 1);
  core.drawBitmap(x + w, 0, bitmapWave, 1);
}

void DrawBottom(GameCore& core, const int beginX) {
  const byte w = bitmapBottom[0];
  const byte y = SCREEN_HEIGHT - bitmapBottom[1];
  const char x = beginX % w;
  core.drawBitmap(x,         y, bitmapBottom, 1);
  core.drawBitmap(x + w,     y, bitmapBottom, 1);
  core.drawBitmap(x + w * 2, y, bitmapBottom, 1);
}

