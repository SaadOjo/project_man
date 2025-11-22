#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dialog.h"
#include "utils.h"
#include "vim_motions.h"

DIALOG_s  DIALOG_make(){
  DIALOG_s s;
  s.win = NULL;

  s.task_tb = NULL;
  s.start_tb = NULL;
  s.duration_tb = NULL;
  s.end_tb = NULL;
  s.depends_tb = NULL;
  s.tb_pl = NULL; 
  s.active_tb = 0;

  s.type = DIALOG_TYPE_NULL;

  return s;
}

void DIALOG_alloc(DIALOG_s* d){
  
  UI_WINDOW_s win;
  win = UI_WINDOW_make();
  win.w = COLS/2;
  win.h = LINES/2;
  win.s_y = (LINES - win.h)/2;
  win.s_x = (COLS - win.w)/2;
  UI_WINDOW_alloc(&win); 

  UI_WINDOW_s* m_w = malloc(sizeof(UI_WINDOW_s));
  memcpy(m_w, &win, sizeof(UI_WINDOW_s));
  d->win = m_w;
  
  // Textbox layout also done here
  TEXTBOX_s tb;
  tb = TEXTBOX_make();
  int w, x;
  w = d->win->w - 4;
  x = (d->win->w - w)/2;
  tb.width = w;
  tb.height = 3;
  tb.x = x;
  tb.y = 2;
  TEXTBOX_alloc(&tb);
  strcpy(tb.label, "[T]ask");
  d->task_tb = malloc(sizeof(TEXTBOX_s));
  memcpy(d->task_tb, &tb, sizeof(TEXTBOX_s));

  tb.width = d->win->w/2 - 2*x;
  tb.y+=3;
  TEXTBOX_alloc(&tb);
  strcpy(tb.label, "[S]tart");
  d->start_tb = malloc(sizeof(TEXTBOX_s));
  memcpy(d->start_tb, &tb, sizeof(TEXTBOX_s));

  tb.x+=(d->win->w/2);
  TEXTBOX_alloc(&tb);
  strcpy(tb.label, "[D]uration (Days)");
  d->duration_tb = malloc(sizeof(TEXTBOX_s));
  memcpy(d->duration_tb, &tb, sizeof(TEXTBOX_s));

  tb.y+=3;
  tb.x = x;
  TEXTBOX_alloc(&tb);
  strcpy(tb.label, "[E]nd");
  d->end_tb = malloc(sizeof(TEXTBOX_s));
  memcpy(d->end_tb, &tb, sizeof(TEXTBOX_s));

  tb.x+=(d->win->w/2);
  TEXTBOX_alloc(&tb);
  strcpy(tb.label, "De[p]ends");
  d->depends_tb = malloc(sizeof(TEXTBOX_s));
  memcpy(d->depends_tb, &tb, sizeof(TEXTBOX_s));

  d->tb_pl = malloc(sizeof(*d->tb_pl)*5);
  d->tb_pl[0] = d->task_tb;
  d->tb_pl[1] = d->start_tb;
  d->tb_pl[2] = d->duration_tb;
  d->tb_pl[3] = d->end_tb;
  d->tb_pl[4] = d->depends_tb;
}

void DIALOG_del(DIALOG_s* d){
  UI_WINDOW_del(d->win);
  free(d->win);

  TEXTBOX_del(d->task_tb);
  free(d->task_tb);

  TEXTBOX_del(d->start_tb);
  free(d->start_tb);

  TEXTBOX_del(d->duration_tb);
  free(d->duration_tb);

  TEXTBOX_del(d->end_tb);
  free(d->end_tb);

  TEXTBOX_del(d->depends_tb);
  free(d->depends_tb);

  free(d->tb_pl);
}

void _DIALOG_draw(DIALOG_s* d){
  UI_WINDOW_s* win = d->win;
  box(win->win, 0, 0);

  char* title; 

  switch(d->type){
    case DIALOG_TYPE_ADD:
      title = "ADD TASK";
      break;
    case DIALOG_TYPE_MODIFY:
      title = "MODIFY TASK";
      break;
    case DIALOG_TYPE_NULL:
      //Not expected case as this should have been set a-priori.
      return;
  }
  mvwaddstr(win->win, 1, (win->w - strlen(title))/2, title);
  
  _DIALOG_active_textbox_attr_update(d);
  TEXTBOX_draw(d->task_tb, d->win);  
  TEXTBOX_draw(d->start_tb, d->win);  
  TEXTBOX_draw(d->duration_tb, d->win);  
  TEXTBOX_draw(d->end_tb, d->win);  
  TEXTBOX_draw(d->depends_tb, d->win);  
}
void DIALOG_show(DIALOG_s *d, app_context_s* a_ctx){
// capture text steam
// Optional, if same task as previously highlighted, highlight the same labeled box
// Clear dialog before exiting
  UI_WINDOW_s* win = d->win;
  WINDOW* n_win = win->win;

  d->active_tb = 0;
  switch(d->type){
    case DIALOG_TYPE_NULL:
      break; // Unexpected case
    case DIALOG_TYPE_ADD:
      _DIALOG_content_clear(d);
      break;
    case DIALOG_TYPE_MODIFY:
    _DIALOG_content_set(d, &a_ctx->ts[a_ctx->hlgt]);
    break;
  }
  _DIALOG_draw(d);
  UI_WINDOW_refresh(win);

  int c;
  while((c = wgetch(n_win)) != 27){
    switch(c){
      case 't': // Task
        d->active_tb = DIALOG_TEXTBOX_TASK;
        _DIALOG_textbox_enter(d, a_ctx);
        break;
      case 's': // Start
        d->active_tb = DIALOG_TEXTBOX_START;
        _DIALOG_textbox_enter(d, a_ctx);
        break;
      case 'd': // Duration
        d->active_tb = DIALOG_TEXTBOX_DURATION;
        _DIALOG_textbox_enter(d, a_ctx);
        break;
      case 'e': // End
        d->active_tb = DIALOG_TEXTBOX_END;
        _DIALOG_textbox_enter(d, a_ctx);
        break;
      case 'p': // Depends
        d->active_tb = DIALOG_TEXTBOX_DEPENDS;
        _DIALOG_textbox_enter(d, a_ctx);
        break;
      case '\t':
        _DIALOG_active_textbox_cycle(d);
        break;
      case '\n': // Should go into "ENTER" mode. 
        _DIALOG_textbox_enter(d, a_ctx);
        break;
    }
    //TODO: Add / update the task
    // Take information from buffer and do something about it
    _DIALOG_draw(d);
    UI_WINDOW_refresh(win);
  }
  
  // TODO: Eventually there should be an explicit save option
  time_t start = UTILS_time_parse(d->start_tb->text);
  double duration = UTILS_duration_parse(d->duration_tb->text);
  time_t end = UTILS_time_parse(d->end_tb->text);
  int idx;

  switch(d->type){
    case DIALOG_TYPE_NULL:
      break; // Unexpected case
    case DIALOG_TYPE_ADD:
      idx = (TASKS_len(a_ctx->ts)==0)?0:a_ctx->hlgt+1;
      TASKS_add(a_ctx->ts, idx, d->task_tb->text, start, duration, end);
      break;
    case DIALOG_TYPE_MODIFY:
      TASKS_modify(a_ctx->ts, a_ctx->hlgt, d->task_tb->text, start, duration, end);
      break;
  }

  UI_WINDOW_clear(win);
  UI_WINDOW_refresh(win);
}

void _DIALOG_active_textbox_cycle(DIALOG_s *d){
  d->active_tb++;
  d->active_tb%=5;

}

void _DIALOG_content_set(DIALOG_s* d, task_s* t){
  _DIALOG_content_clear(d);
  struct tm* ts;
  char buff[1024];
  // Task name
  strcpy(d->task_tb->text, t->name);
  // Start 
  ts = localtime(&t->start);
  strftime(buff, sizeof(buff), "%d/%m/%y", ts);
  strcpy(d->start_tb->text, buff);
  // Duration
  int dur = (int)t->duration/86400.0;
  sprintf(buff, "%d", dur);
  strcpy(d->duration_tb->text, buff);
  // End 
  ts = localtime(&t->end);
  strftime(buff, sizeof(buff), "%d/%m/%y", ts);
  strcpy(d->end_tb->text, buff);
  // Depends
  strcpy(d->depends_tb->text, "HC");
}

void _DIALOG_content_clear(DIALOG_s* d){
  d->task_tb->text[0] = '\0';
  d->start_tb->text[0] = '\0';
  d->duration_tb->text[0] = '\0';
  d->end_tb->text[0] = '\0';
  d->depends_tb->text[0] = '\0';
}

void _DIALOG_active_textbox_attr_update(DIALOG_s *d){
  TEXTBOX_s* tb;
  for(int i=0; i<5; i++){
    tb = d->tb_pl[i];
    if(tb->state == TEXTBOX_STATE_ENTER){
      continue;
    }
    tb->state = i==d->active_tb?TEXTBOX_STATE_HIGHLIGHT:TEXTBOX_STATE_DEFAULT;
  }
}

void _DIALOG_textbox_enter(DIALOG_s* d, app_context_s* a_ctx){
  const int NORMAL_MODE = 1;
  const int INSERT_MODE = 2; 
  int mode = NORMAL_MODE;
  int cur_idx = 0;
  bool running = true;
  int ch; 
  TEXTBOX_s* active_tb = d->tb_pl[d->active_tb];
  active_tb->state = TEXTBOX_STATE_ENTER;
  curs_set(1);
  _DIALOG_draw(d);
  wmove(d->win->win, active_tb->y+1, active_tb->x+1);
  UI_WINDOW_refresh(d->win);

  //Normal mode init

  int suffix_len;
  while(running){
    ch = wgetch(d->win->win);
    if(mode == NORMAL_MODE){
      switch(ch){
        case 27:
          running = false;
          break;
        case 'a':
          mode = INSERT_MODE;
          cur_idx++;
          printf("\033[6 q");
          fflush(stdout);
          break;
        case 'i':
          mode = INSERT_MODE;
          printf("\033[6 q");
          fflush(stdout);
          break;
        case 'l':
          cur_idx = vim_l(active_tb->text, cur_idx);
          break;
        case 'h':
          cur_idx = vim_h(active_tb->text, cur_idx);
          break;
        case 'b':
          cur_idx = vim_b(active_tb->text, cur_idx);
          break;
        case 'w':
          cur_idx = vim_w(active_tb->text, cur_idx);
          break;
        case 'e':
          cur_idx = vim_e(active_tb->text, cur_idx);
          break;
      }
    } else if(mode == INSERT_MODE){
      switch(ch){
        case 27:
          mode = NORMAL_MODE;
          cur_idx--;
          if (cur_idx < 0){
            cur_idx = 0;
          }
          printf("\033[0 q");
          fflush(stdout);
          break;
        case 127:
          if(cur_idx == 0){
            break;
          }
          suffix_len = strlen(active_tb->text+cur_idx);
          memmove(active_tb->text+cur_idx - 1, active_tb->text+cur_idx, suffix_len + 1);
          cur_idx--;
          break;
        default: // Entering text
          suffix_len = strlen(active_tb->text+cur_idx);
          memmove(active_tb->text+cur_idx+1, active_tb->text+cur_idx, suffix_len + 1);
          active_tb->text[cur_idx] = ch;
          cur_idx++;
          break;
      }
    }
    _DIALOG_draw(d);
    wmove(d->win->win, active_tb->y+1, active_tb->x+1+cur_idx);
    UI_WINDOW_refresh(d->win);
  } 
  // TODO: Validate the text entry
  // TODO: Validate update the other fields accordingly
  _DIALOG_recalculate(d, a_ctx);

  d->tb_pl[d->active_tb]->state = TEXTBOX_STATE_HIGHLIGHT;
  curs_set(0);
  _DIALOG_draw(d);
  UI_WINDOW_refresh(d->win);
}

void _DIALOG_recalculate(DIALOG_s* d, app_context_s* a_ctx){
  struct tm* tm_ptr;
  time_t start;
  time_t end;
  double dur;
  char* str_ptr;

  switch(d->active_tb){
    case DIALOG_TEXTBOX_TASK:
      break;
    case DIALOG_TEXTBOX_START:
      // This should already have been validated at this point
      if(strlen(d->start_tb->text) == 0){
        break;
      }
      if(strlen(d->duration_tb->text) == 0){
        break;
      }
      start = UTILS_time_parse(d->start_tb->text);
      end = start + UTILS_duration_parse(d->duration_tb->text); 
      tm_ptr = localtime(&end);
      str_ptr = d->end_tb->text;
      strftime(str_ptr, sizeof(str_ptr), "%d/%m/%y", tm_ptr);
      break;
    case DIALOG_TEXTBOX_DURATION:
      // Replace with validation
      if(strlen(d->duration_tb->text) == 0){
        break;
      }
      if(strlen(d->start_tb->text) == 0){
        break;
      }
      start = UTILS_time_parse(d->start_tb->text);
      end = start + UTILS_duration_parse(d->duration_tb->text); 
      tm_ptr = localtime(&end);
      str_ptr = d->end_tb->text;
      strftime(str_ptr, sizeof(str_ptr), "%d/%m/%y", tm_ptr);
      break;
    case DIALOG_TEXTBOX_END:
      // Replace with validation
      if(strlen(d->end_tb->text) == 0){
        break;
      }
      if(strlen(d->start_tb->text) == 0 || strlen(d->duration_tb->text) == 0){
        return;
      }
      start = UTILS_time_parse(d->start_tb->text);
      end = UTILS_time_parse(d->end_tb->text);
      dur = difftime(end, start);
      if(dur < 0){
        strcpy(d->end_tb->text, d->start_tb->text);
        dur = 0.0;
      }
      sprintf(d->duration_tb->text, "%d", (int)dur/(24*60*60));
      break;
    case DIALOG_TEXTBOX_DEPENDS:
      // Add dependency updates
      break;
  }
}
