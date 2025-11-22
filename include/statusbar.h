#pragma once

#include "ui_window.h"

typedef enum {
  STATUSBAR_MODE_NORMAL,
  STATUSBAR_MODE_INSERT,
  STATUSBAR_MODE_VISUAL,
  STATUSBAR_MODE_COMMAND
} STATUSBAR_mode_e;

typedef struct STATUSBAR_s {
 UI_WINDOW_s* win; 
 STATUSBAR_mode_e m;
  // command
} STATUSBAR_s;


STATUSBAR_s STATUSBAR_make();
void        STATUSBAR_alloc(STATUSBAR_s* sb); 
void        STATUSBAR_del(STATUSBAR_s* sb);
void        STATUSBAR_reflect(STATUSBAR_s* sb);
// Private functions
void        _STATUSBAR_draw(STATUSBAR_s* sb);
