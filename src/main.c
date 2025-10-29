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
  UTILS_ui_init();
  refresh(); 
  UI_WINDOW_s h_w = UI_WINDOW_make();
  h_w.w = COLS;
  h_w.h = 3;
  UI_WINDOW_alloc(&h_w); 
  UI_WINDOW_center_addstr(&h_w, "Project Man");
  UI_WINDOW_refresh(&h_w);
  TASKS_sl ts = TASKS_make();

  UI_WINDOW_s m_w = UI_WINDOW_make();
  m_w.w = COLS;
  m_w.h = LINES - 3;
  m_w.s_y = 3;
  UI_WINDOW_alloc(&m_w); 

  app_context_s a_ctx = UTILS_app_context_make();
  a_ctx.m_w = &m_w;
  a_ctx.ts = ts;

  TASKS_add(ts, "Persons have done", 0, 0);
  TASKS_add(ts, "Sign Supply Chain Agreement", 0, 0);
  TASKS_add(ts, "Prepare Logistics Agreement Draft", 0, 0);
  TASKS_add(ts, "Review EVT Device", 0, 0);
  TASKS_add(ts, "Review DVT Device", 0, 0);
  TASKS_add(ts, "Revise Project Budget", 0, 0);
  TASKS_add(ts, "Prepare Project Book", 0, 0);
  TASKS_add(ts, "Prepare Project Book", 0, 0);
  TASKS_add(ts, "Prepare Project Book", 0, 0);
  TASKS_add(ts, "Prepare Project Book", 0, 0);

  UTILS_render_tasks(&a_ctx);
  UI_WINDOW_refresh(&m_w);

  UI_WINDOW_s d_w = UI_WINDOW_make();
  d_w.w = COLS/2;
  d_w.h = LINES/2;
  d_w.s_y = (LINES - d_w.h)/2;
  d_w.s_x = (COLS - d_w.w)/2;
  UI_WINDOW_alloc(&d_w); 
  a_ctx.d_w = &d_w;

  int c;
  while((c=getch()) != 'q'){
    UTILS_navigate(&a_ctx, c);
  }
  // Resoruce cleanup
  UI_WINDOW_del(&h_w);
  UI_WINDOW_del(&m_w);
  UI_WINDOW_del(&d_w);
  endwin();
  return 0;
}

