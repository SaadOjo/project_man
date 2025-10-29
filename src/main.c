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
  UI_window_s h_w = UI_Window_make();
  h_w.w = COLS;
  h_w.h = 3;
  UI_create_window(&h_w); 
  UI_waddstr_center(&h_w, "Project Man");
  UI_wrefresh(&h_w);
  tasks_sl ts = TASKS_make();

  UI_window_s m_w = UI_Window_make();
  m_w.w = COLS;
  m_w.h = LINES - 3;
  m_w.s_y = 3;
  UI_create_window(&m_w); 

  app_context_s a_ctx;
  a_ctx.m_w = &m_w;
  a_ctx.ts = ts;
  a_ctx.hlgt = 2;

  TASKS_add(ts, 0, "Persons have done", 0, 0);
  TASKS_add(ts, 1, "Sign Supply Chain Agreement", 0, 0);
  TASKS_add(ts, 2, "Prepare Logistics Agreement Draft", 0, 0);
  TASKS_add(ts, 3, "Review EVT Device", 0, 0);
  TASKS_add(ts, 4, "Review DVT Device", 0, 0);
  TASKS_add(ts, 5, "Revise Project Budget", 0, 0);
  TASKS_add(ts, 6, "Prepare Project Book", 0, 0);

  UI_render_tasks(&a_ctx);
  UI_wrefresh(&m_w);

  UI_window_s d_w = UI_Window_make();
  d_w.w = COLS/2;
  d_w.h = LINES/2;
  d_w.s_y = (LINES - d_w.h)/2;
  d_w.s_x = (COLS - d_w.w)/2;
  UI_create_window(&d_w); 
  a_ctx.d_w = &d_w;

  int c;
  while((c=getch()) != 'q'){
    UTILS_navigate(&a_ctx, c);
  }
  getch();
  // Resoruce cleanup
  UI_Window_del(&h_w);
  UI_Window_del(&m_w);
  UI_Window_del(&d_w);
  endwin();
  return 0;
}

