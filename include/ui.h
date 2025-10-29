#pragma once
#include <ncurses.h>
#include "structs.h"

typedef struct UI_window_s{
  WINDOW *win;
  int w;
  int h;
  int s_x;
  int s_y;
} UI_window_s;

UI_window_s UI_Window_make();
void UI_Window_del(UI_window_s* w);
void UI_init();
void UI_create_window(UI_window_s* w);
void UI_waddstr_center(UI_window_s* w, char* m);
void UI_wrefresh(UI_window_s* w); 
void UI_render_tasks(app_context_s* a_ctx);
void UI_render_modal(app_context_s* a_ctx);
