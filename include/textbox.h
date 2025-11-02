#pragma once
#include <ncurses.h>

#include "ui_window.h"

#define TEXTBOX_LABEL_FOCUS_ATTR A_BOLD | A_REVERSE
#define TEXTBOX_BORDER_FOCUS_ATTR A_BOLD 

typedef enum {
  TEXTBOX_STATE_DEFAULT, 
  TEXTBOX_STATE_NORMAL, 
  TEXTBOX_STATE_INSERT 
} TEXTBOX_state_e;

typedef struct TEXTBOX_s {
  TEXTBOX_state_e state;
  int width;
  int height;
  int y;
  int x;
  char* label;
  char* text;

} TEXTBOX_s;

TEXTBOX_s TEXTBOX_make();
void      TEXTBOX_alloc(TEXTBOX_s* tb);
void      TEXTBOX_del(TEXTBOX_s* tb);

void      TEXTBOX_draw(TEXTBOX_s* tb, UI_WINDOW_s* win);
