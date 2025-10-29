#include "ui.h"
#include "structs.h"

UI_window_s UI_Window_make(){
  UI_window_s w;
  w.win = NULL;
  w.w = 10;
  w.h = 3;
  w.s_x = 0;
  w.s_y = 0;
  return w;
}

void UI_Window_del(UI_window_s* w){
  if(w->win == NULL){
    return;
  }
  delwin(w->win);
}

void UI_init(){
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

void UI_create_window(UI_window_s* w){
  if(w->win == NULL){
    w->win = newwin(w->h, w->w, w->s_y, w->s_x);
  }
  box(w->win, 0, 0);
}

void UI_waddstr_center(UI_window_s* w, char* m){
  mvwaddstr(w->win, w->h/2, (w->w - strlen(m))/2, m); 
}

void UI_wrefresh(UI_window_s* w){
  wrefresh(w->win);
}

void UI_render_tasks(app_context_s* a_ctx){
  UI_window_s* w = a_ctx->m_w;
  tasks_sl* ts = a_ctx->ts;
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
    tasks_sl t = ts[i];

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
void UI_render_modal(app_context_s *a_ctx){

}
