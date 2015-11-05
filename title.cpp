#include "title.h"
#include "gamecore.h"
#include "util.h"

// Logo.png / 48x38
PROGMEM const unsigned char bitmapLogo[] = {
  48, 38,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x60, 0x18, 0x87, 0xC1, 0x31, 0x0A, 0x0E, 0x08, 
  0x08, 0x08, 0x08, 0x18, 0x38, 0xF8, 0xF8, 0xF8, 0xF8, 0x38, 
  0x18, 0x08, 0x08, 0x0C, 0xF2, 0x02, 0x02, 0xF4, 0x08, 0x00, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x38, 0xFE, 0x07, 
  0x0C, 0xD2, 0x21, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
  0x04, 0x04, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x04, 0x04, 
  0x04, 0x04, 0xFF, 0x00, 0x00, 0xFF, 0x06, 0x05, 0x04, 0x05, 
  0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x04, 0x03, 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
  0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x02, 0x02, 0x02, 0x02, 
  0x07, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x10, 0x0F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x30, 0x38, 0x3F, 
  0x3F, 0x3F, 0x3F, 0x38, 0x30, 0x20, 0x20, 0x20, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x3E, 0x0A, 0x00, 0x38, 0x28, 0x38, 
  0x00, 0x38, 0x10, 0x08, 0x00, 0x00, 0x3C, 0x12, 0x12, 0x3C, 
  0x00, 0x3E, 0x0A, 0x1A, 0x24, 0x00, 0x3E, 0x22, 0x22, 0x1C, 
  0x00, 0x1E, 0x20, 0x20, 0x1E, 0x00, 0x3E, 0x2A, 0x2A, 0x14, 
  0x00, 0x1C, 0x22, 0x22, 0x1C, 0x00, 0x0E, 0x38, 0x38, 0x0E
};

int Title::loop(GameCore& core) {
  // controls
  // up
  if(core.pressed(BTN_U) && !prevUpButton) {
    --cursor;
    if(cursor < TITLE_START_GAME) { cursor = TITLE_DISP_RANKING; }
  }
  prevUpButton = core.pressed(BTN_U);
  // down
  if(core.pressed(BTN_D) && !prevDownButton) {
    ++cursor;
    if(cursor > TITLE_DISP_RANKING) { cursor = TITLE_START_GAME; }
  }
  prevDownButton = core.pressed(BTN_D);
  // enter
  bool enterButton = core.pressed(BTN_A) || core.pressed(BTN_B);
  if(enterButton && !prevEnterButton) {
    if(cursor == TITLE_TOGGLE_SOUND) {
      core.soundOn = !core.soundOn;
    }
    else {
      prevEnterButton = true;
      return TITLE_START_GAME;
    }
  }
  prevEnterButton = enterButton;

  // drawing
  draw(core);
  
  return TITLE_NOINPUT;
}

void Title::draw(GameCore& core) {
  core.drawBitmap(10, SCREEN_HEIGHT/2 - bitmapLogo[1]/2 - 1, bitmapLogo, 1);
  DrawWave(core, 0, core.frameCount());
  DrawBottom(core, 0);

  core.setCursor(70, 15);
  core.print("START");
  
  core.setCursor(70, 28);
  core.print("SOUND");
  core.setCursor(105, 28);
  if(core.soundOn) { core.print("ON"); }
  else { core.print("OFF"); }
  
  core.setCursor(70, 41);
  core.print("RANKING");

  core.setCursor(63, (cursor-1) * 13 + 15);
  core.print(">");
}

