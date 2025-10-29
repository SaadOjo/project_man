#include "utils.h"
#include "ui.h"

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
  }
  UI_render_tasks(a);
  UI_wrefresh(a->m_w); 

  UI_render_modal(a);
  UI_wrefresh(a->d_w);
}

