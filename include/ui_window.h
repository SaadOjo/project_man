#pragma once
#include <ncurses.h>

#include "structs.h"

typedef struct UI_WINDOW_s{
  WINDOW *win;
  int w;
  int h;
  int s_x;
  int s_y;
} UI_WINDOW_s;

UI_WINDOW_s UI_WINDOW_make();
void UI_WINDOW_alloc(UI_WINDOW_s* w);
void UI_WINDOW_del(UI_WINDOW_s* w);

void UI_WINDOW_center_addstr(UI_WINDOW_s* w, char* m);
void UI_WINDOW_refresh(UI_WINDOW_s* w); 

