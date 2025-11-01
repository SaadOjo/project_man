#include "dialog.h"
#include <stdlib.h>

DIALOG_s  DIALOG_make(){
  DIALOG_s s;
  s.win = NULL;
  s.contents = NULL;
  s.active_textbox = DIALOG_TEXTBOX_TASK; 
  s.type = DIALOG_TYPE_NULL; 
  return s;
}
void DIALOG_alloc(DIALOG_s* d){
  
  UI_WINDOW_s w;
  w = UI_WINDOW_make();
  w.w = COLS/2;
  w.h = LINES/2;
  w.s_y = (LINES - w.h)/2;
  w.s_x = (COLS - w.w)/2;
  UI_WINDOW_alloc(&w); 

  UI_WINDOW_s* m_w = malloc(sizeof(UI_WINDOW_s));
  memcpy(m_w, &w, sizeof(UI_WINDOW_s));
  d->win = m_w;
  
  DIALOG_contents_s* cnt = malloc(sizeof(DIALOG_contents_s));

  EDITABLE_TEXT_s et;
  EDITABLE_TEXT_s* m_et;

  et = EDITABLE_TEXT_make();
  EDITABLE_TEXT_alloc(&et);
  m_et = malloc(sizeof(EDITABLE_TEXT_s));
  memcpy(m_et, &et, sizeof(EDITABLE_TEXT_s));
  cnt->task = m_et;

  et = EDITABLE_TEXT_make();
  EDITABLE_TEXT_alloc(&et);
  m_et = malloc(sizeof(EDITABLE_TEXT_s));
  memcpy(m_et, &et, sizeof(EDITABLE_TEXT_s));
  cnt->duration = m_et;

  et = EDITABLE_TEXT_make();
  EDITABLE_TEXT_alloc(&et);
  m_et = malloc(sizeof(EDITABLE_TEXT_s));
  memcpy(m_et, &et, sizeof(EDITABLE_TEXT_s));
  cnt->start = m_et;

  et = EDITABLE_TEXT_make();
  EDITABLE_TEXT_alloc(&et);
  m_et = malloc(sizeof(EDITABLE_TEXT_s));
  memcpy(m_et, &et, sizeof(EDITABLE_TEXT_s));
  cnt->end = m_et;

  et = EDITABLE_TEXT_make();
  EDITABLE_TEXT_alloc(&et);
  m_et = malloc(sizeof(EDITABLE_TEXT_s));
  memcpy(m_et, &et, sizeof(EDITABLE_TEXT_s));
  cnt->depends = m_et;
  
  d->contents = cnt;  
}

void DIALOG_del(DIALOG_s* d){
  UI_WINDOW_del(d->win);
  free(d->win);
  DIALOG_contents_s* cnt = d->contents;
  EDITABLE_TEXT_del(cnt->task);
  EDITABLE_TEXT_del(cnt->duration);
  EDITABLE_TEXT_del(cnt->start);
  EDITABLE_TEXT_del(cnt->end);
  EDITABLE_TEXT_del(cnt->depends);
  free(cnt);
}

void DIALOG_render(DIALOG_s* d){
  UI_WINDOW_s* win = d->win;
  box(win->win, 0, 0);

  char* title; 

  switch(d->type){
    case DIALOG_TYPE_ADD:
      title = "INSERT TASK";
      break;
    case DIALOG_TYPE_MODIFY:
      title = "MODIFY TASK";
      break;
    case DIALOG_TYPE_NULL:
      //Not expected case as this should have been set a-priori.
      return;
  }
  mvwaddstr(win->win, 1, (win->w - strlen(title))/2, title);
  
  int w, s_x;
  w = win->w - 4;
  s_x = (win->w - w)/2;
  
  attr_t highlight_attr = A_BOLD | A_REVERSE;
  attr_t attr;

  attr = d->active_textbox == DIALOG_TEXTBOX_TASK ? highlight_attr : A_NORMAL;
  UI_WINDOW_labeled_rectangle_draw(win, 2, s_x, w, "Task", attr);
  
  int tw = w;
  int ts_x = s_x;

  w = win->w/2 - 2;
  attr = d->active_textbox == DIALOG_TEXTBOX_DURATION ? highlight_attr : A_NORMAL;
  UI_WINDOW_labeled_rectangle_draw(win, 5, ts_x, w, "Duration", attr);

  s_x = tw + ts_x - w; 
  attr = d->active_textbox == DIALOG_TEXTBOX_START ? highlight_attr : A_NORMAL;
  UI_WINDOW_labeled_rectangle_draw(win, 5, s_x, w, "Start", attr);

  attr = d->active_textbox == DIALOG_TEXTBOX_END ? highlight_attr : A_NORMAL;
  UI_WINDOW_labeled_rectangle_draw(win, 8, ts_x, w, "End", attr);

  attr = d->active_textbox == DIALOG_TEXTBOX_DEPENDS ? highlight_attr : A_NORMAL;
  UI_WINDOW_labeled_rectangle_draw(win, 8, s_x, w, "Depends", attr);
}
void DIALOG_navigate(DIALOG_s *d, app_context_s* a_ctx){
// capture text steam
// Optional, if same task as previously highlighted, highlight the same labeled box
// Clear dialog before exiting
  UI_WINDOW_s* win = d->win;
  WINDOW* n_win = win->win;
 
  DIALOG_render(d);
  UI_WINDOW_refresh(win);

  int c;
  while((c = wgetch(n_win)) != 27){
    switch(c){
      case 'j':
        break;
      case '\t':
        _DIALOG_cycle_active_textbox(d);
        break;
      case '\n': // Should go into "NORMAL" mode. 
        break;
    }
    //TODO: Add / update the task
    // Take information from buffer and do something about it
    DIALOG_render(d);
    UI_WINDOW_refresh(win);
  }

  wclear(n_win); 
  UI_WINDOW_refresh(win);
}

void _DIALOG_cycle_active_textbox(DIALOG_s *d){
  d->active_textbox++;
  d->active_textbox%=5;
}
