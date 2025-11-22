#include "statusbar.h"

STATUSBAR_s STATUSBAR_make(){
  STATUSBAR_s sb;
  sb.m = STATUSBAR_MODE_NORMAL;
  sb.win = NULL;
  return sb;
}

void STATUSBAR_alloc(STATUSBAR_s* sb){
  UI_WINDOW_s win;
  win = UI_WINDOW_make();
  win.w = COLS;
  win.h = 3;
  win.s_y = LINES - 3;
  win.s_x = 0;
  UI_WINDOW_alloc(&win); 

  UI_WINDOW_s* w = malloc(sizeof(UI_WINDOW_s));
  memcpy(w, &win, sizeof(UI_WINDOW_s));
  sb->win = w;
}
void STATUSBAR_del(STATUSBAR_s* sb){
  UI_WINDOW_del(sb->win);
  free(sb->win);
}
void STATUSBAR_reflect(STATUSBAR_s* sb){
  _STATUSBAR_draw(sb);
  UI_WINDOW_refresh(sb->win);
}

void _STATUSBAR_draw(STATUSBAR_s* sb){
  UI_WINDOW_clear(sb->win);

  WINDOW* nw = sb->win->win;
  box(nw, 0, 0);

  char buff[1024];

  switch(sb->m){
    case STATUSBAR_MODE_NORMAL:
      strcpy(buff, "--NORMAL--");
      break;
    case STATUSBAR_MODE_INSERT:
      strcpy(buff, "--INSERT--");
      break;
    case STATUSBAR_MODE_VISUAL:
      strcpy(buff, "--VISUAL--");
      break;
    case STATUSBAR_MODE_COMMAND:
      break;
  }
  mvwaddstr(nw, 1, 2, buff);
}
