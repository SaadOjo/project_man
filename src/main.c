#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "structs.h"
#include "tasks.h"
#include "utils.h"
#include "ui_window.h"
#include "structs.h"
#include "dialog.h"

int main(void){
  // Header Window
  UTILS_ui_init();
  refresh(); 
  UI_WINDOW_s h_w = UI_WINDOW_make();
  h_w.w = COLS;
  h_w.h = 3;
  UI_WINDOW_alloc(&h_w); 
  UI_WINDOW_center_addstr(&h_w, "Project Man - by Saad Saif");
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

  UTILS_render_tasks(&a_ctx);
  UI_WINDOW_refresh(&m_w);

  DIALOG_s d = DIALOG_make();
  DIALOG_alloc(&d);
  a_ctx.d = &d; 

  int c;
  while((c=getch()) != 'q'){
    UTILS_navigate(&a_ctx, c);
  }
  // Resoruce cleanup
  // Perhaps would be better if we could have a single function call for a_ctx cleanup
  UI_WINDOW_del(&h_w);
  UI_WINDOW_del(&m_w);
  DIALOG_del(&d);
  endwin();
 // TASKS_del(ts);
  return 0;
}

