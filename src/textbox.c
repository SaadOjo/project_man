#include "textbox.h"

#define TEXTBOX_MAX_LEN 1024

TEXTBOX_s TEXTBOX_make(){
  TEXTBOX_s tb;
  tb.state = TEXTBOX_STATE_DEFAULT;
  tb.width = 10;
  tb.height = 3;
  tb.x = 0;
  tb.y = 0;
  tb.label = NULL;
  tb.text = NULL;

  return tb;
}
void TEXTBOX_alloc(TEXTBOX_s* tb){
  tb->text = calloc(TEXTBOX_MAX_LEN, sizeof(char));
  tb->label = calloc(TEXTBOX_MAX_LEN, sizeof(char));
}
void TEXTBOX_del(TEXTBOX_s* tb){
  free(tb->text);
  free(tb->label);
}

void TEXTBOX_draw(TEXTBOX_s* tb, UI_WINDOW_s* win){
  int x = tb->x;
  int y = tb->y;
  int width = tb->width;
  int height = tb->height;
  WINDOW* n_win  = win->win;
  char* label = tb->label;
  char* text = tb->text;
  attr_t label_attr = A_NORMAL; 
  attr_t border_attr = A_NORMAL;
 
  switch(tb->state){
    case TEXTBOX_STATE_DEFAULT:
      break;
    case TEXTBOX_STATE_HIGHLIGHT:
      label_attr = TEXTBOX_LABEL_FOCUS_ATTR;
      break;
    case TEXTBOX_STATE_ENTER:
      border_attr = TEXTBOX_BORDER_FOCUS_ATTR;
      label_attr = A_UNDERLINE;
      break;
  }

  wattron(n_win, border_attr);
  mvwhline(n_win, y, x + 1, ACS_HLINE, width - 2); 
  mvwhline(n_win, y + height - 1, x + 1, ACS_HLINE, width - 2); 

  mvwvline(n_win, y + 1, x, ACS_VLINE, height - 2); 
  mvwvline(n_win, y + 1, x + width - 1, ACS_VLINE, height - 2); 

  mvwaddch(n_win, y, x, ACS_ULCORNER);
  mvwaddch(n_win, y, x + width - 1, ACS_URCORNER);
  mvwaddch(n_win, y + height - 1, x, ACS_LLCORNER);
  mvwaddch(n_win, y + height - 1, x + width - 1, ACS_LRCORNER);
  wattroff(n_win, border_attr);

  wattron(n_win, label_attr);
  mvwaddstr(n_win, y, x + 2, label);
  wattroff(n_win, label_attr);

  mvwaddstr(n_win, y + 1, x + 1, text);
}
