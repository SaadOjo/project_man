#include "ui_window.h"
#include "structs.h"

UI_WINDOW_s UI_WINDOW_make(){
  UI_WINDOW_s w;
  w.win = NULL;
  w.w = 10;
  w.h = 3;
  w.s_x = 0;
  w.s_y = 0;
  return w;
}

void UI_WINDOW_del(UI_WINDOW_s* w){
  if(w->win == NULL){
    return;
  }
  delwin(w->win);
}
// Arguably if the window is already allocated we should return error. Let's think about it. 
void UI_WINDOW_alloc(UI_WINDOW_s* w){
  if(w->win == NULL){
    w->win = newwin(w->h, w->w, w->s_y, w->s_x);
  }
  box(w->win, 0, 0);
}

void UI_WINDOW_center_addstr(UI_WINDOW_s* w, char* m){
  mvwaddstr(w->win, w->h/2, (w->w - strlen(m))/2, m); 
}

void UI_WINDOW_refresh(UI_WINDOW_s* w){
  wrefresh(w->win);
}
void UI_WINDOW_clear(UI_WINDOW_s *w){
  wclear(w->win);
  box(w->win, 0, 0);
}
