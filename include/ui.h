#pragma once
#include <ncurses.h>
#include "structs.h"

typedef struct UI_Window{
  WINDOW *win;
  int w;
  int h;
  int s_x;
  int s_y;
} UI_Window;

UI_Window UI_Window_make();
void UI_init();
void UI_create_window(UI_Window* w);
void UI_waddstr_center(UI_Window* w, char* m);
void UI_wrefresh(UI_Window* w); 
void UI_render_tasks(App_context* a_ctx);
