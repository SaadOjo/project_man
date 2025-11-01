#pragma once
#include <ncurses.h>

#include "structs.h"
#include "editable_text.h"

typedef struct UI_WINDOW_s{
  WINDOW *win;
  int w;
  int h;
  int s_x;
  int s_y;
} UI_WINDOW_s;

typedef struct UI_WINDOW_editable_text_s{
  char* text;
  int cursor;
}UI_WINDOW_editable_text_s;

UI_WINDOW_s UI_WINDOW_make();
void UI_WINDOW_alloc(UI_WINDOW_s* w);
void UI_WINDOW_del(UI_WINDOW_s* w);

void UI_WINDOW_center_addstr(UI_WINDOW_s* w, char* m);
void UI_WINDOW_refresh(UI_WINDOW_s* w); 
void UI_WINDOW_labeled_rectangle_draw(UI_WINDOW_s* w, int s_y, int s_x, int width, char* label_title, attr_t label_attr, EDITABLE_TEXT_s* et);

