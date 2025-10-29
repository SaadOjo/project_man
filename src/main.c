#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "structs.h"
#include "tasks.h"
#include "utils.h"
#include "ui.h"
#include "structs.h"

int main(void){
  // Header Window
  UI_init();
  refresh(); 
  UI_Window h_w = UI_Window_make();
  h_w.w = COLS;
  h_w.h = 3;
  UI_create_window(&h_w); 
  UI_waddstr_center(&h_w, "Project Man");
  UI_wrefresh(&h_w);
  Task* ts = Tasks_make();

  UI_Window m_w = UI_Window_make();
  m_w.w = COLS;
  m_w.h = LINES - 3;
  m_w.s_y = 3;
  UI_create_window(&m_w); 

  App_context app_ctx;
  app_ctx.m_w = &m_w;
  app_ctx.ts = ts;
  app_ctx.hlgt = 2;

  Tasks_add(ts, 0, "Persons have done", 0, 0);
  Tasks_add(ts, 1, "Sign Supply Chain Agreement", 0, 0);
  Tasks_add(ts, 2, "Prepare Logistics Agreement Draft", 0, 0);
  Tasks_add(ts, 3, "Review EVT Device", 0, 0);
  Tasks_add(ts, 4, "Review DVT Device", 0, 0);
  Tasks_add(ts, 5, "Revise Project Budget", 0, 0);
  Tasks_add(ts, 6, "Prepare Project Book", 0, 0);

  UI_render_tasks(&app_ctx);
  UI_wrefresh(&m_w);
  int c;
  while((c=getch()) != 'q'){
    UTILS_navigate(&app_ctx, c);
  }

  endwin();
  return 0;
}

