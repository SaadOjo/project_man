#include "utils.h"
#include "ui.h"

void UTILS_ui_init(){
  initscr();
  if(has_colors() == FALSE){
    endwin();
    puts("Your terminal does not support color. Exiting..");
    exit(1);
  }
  curs_set(0);
  puts("Your terminal has color..");
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
}

app_context_s UTILS_app_context_make(){
  app_context_s a_ctx;
  a_ctx.m_w = NULL;
  a_ctx.d_w = NULL;
  a_ctx.ts = NULL;
  a_ctx.s = MODAL_STATE_OFF;
  a_ctx.hlgt = 0;
  return a_ctx;
}
void UTILS_navigate(app_context_s* a, int ch){
  int max_rows = a->m_w->h;
  int ts_len = TASKS_len(a->ts);
  if(ts_len < max_rows){
    max_rows = ts_len;
  }
  switch(ch){
    case 'j':
      a->hlgt = (++a->hlgt)%max_rows;
      break;
    case 'k':
      a->hlgt = (a->hlgt+=(max_rows - 1))%max_rows;
      break;
    case '\n':
      a->s = MODAL_STATE_ON;
      break;
    case 27:
      a->s = MODAL_STATE_OFF;
      wclear(a->d_w->win); //TODO: Integrate with UI_WINDOW library
      UI_WINDOW_refresh(a->d_w);
      break;
  }
  UTILS_render_tasks(a);
  UI_WINDOW_refresh(a->m_w); 
  modal_state_e s = a->s;
  if(s == MODAL_STATE_ON){
    UTILS_render_modal(a);
    UI_WINDOW_refresh(a->d_w);
  }
}

void UTILS_render_tasks(app_context_s* a_ctx){
  UI_WINDOW_s* w = a_ctx->m_w;
  TASKS_sl ts = a_ctx->ts;
  int hlgt = a_ctx->hlgt; 

  int col_w[] = {5, 36, 12, 12};

  // Print the table header
  attr_t attr = A_BOLD; 
  wattron(w->win, attr);
  mvwprintw(w->win, 1, 1, "%-*s%-*s%-*s%-*s",
            col_w[0], "ID",
            col_w[1], "NAME",
            col_w[2], "DURATION",
            col_w[3], "START");
  wattroff(w->win, attr);

  // Printing the rows
  for(int i=0; i<w->h; i++){
    task_s t = ts[i];

    int id = t.id; 
    char* name = t.name;

    if(name == NULL){
      break;  
    }
    attr_t attr = i==hlgt ? A_UNDERLINE | A_BOLD | A_REVERSE : A_NORMAL; 
    wattron(w->win, attr);
    mvwprintw(w->win, i+2, 1, "%-*d%-*s%-*s%-*s",
              col_w[0], id,
              col_w[1], name,
              col_w[2], "12 Days",
              col_w[3], "12-MAY-25");
    wattroff(w->win, attr);
  }
}
void UTILS_render_modal(app_context_s *a_ctx){
  UI_WINDOW_s* win = a_ctx->d_w;
  box(win->win, 0, 0);

  char* title = "INSERT/MODIFY TASK";
  mvwaddstr(win->win, 1, (win->w - strlen(title))/2, title);
  
  int w, s_x;
  w = win->w - 4;
  s_x = (win->w - w)/2;
  UI_WINDOW_labeled_rectangle_draw(win, 2, s_x, w, "Task");
  
  int tw = w;
  int ts_x = s_x;

  w = win->w/2 - 2;
  UI_WINDOW_labeled_rectangle_draw(win, 5, ts_x, w, "Duration");

  w = win->w/2 - 2;
  s_x = tw + ts_x - w; 
  UI_WINDOW_labeled_rectangle_draw(win, 5, s_x, w, "Start");
}
