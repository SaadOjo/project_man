#include <time.h>
#include <stdlib.h>

#include "utils.h"
#include "dialog.h"
#include "ui_window.h"

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
  a_ctx.d = NULL;
  a_ctx.ts = NULL;
  a_ctx.hlgt = 0;
  return a_ctx;
}
void UTILS_navigate(app_context_s* a, int ch){
  int max_rows = a->m_w->h;
  int ts_len = TASKS_len(a->ts);
  DIALOG_s* d = a->d;
  if(ts_len < max_rows){
    max_rows = ts_len;
  }
  switch(ch){
    case 'j':
      if(max_rows == 0){
        break;
      }
      a->hlgt = (++a->hlgt)%max_rows;
      break;
    case 'k':
      if(max_rows == 0){
        break;
      }
      a->hlgt = (a->hlgt+=(max_rows - 1))%max_rows;
      break;
    case '\n':
      // Add check if table is empty, in that case present an error message
      if(TASKS_len(a->ts) == 0){
        break;
      }
      d->type = DIALOG_TYPE_MODIFY;
      DIALOG_show(d, a);
      break;
    case 'a': // Add
      d->type = DIALOG_TYPE_ADD;
      DIALOG_show(d, a);
      break;
    case 'd': // Add
      if(TASKS_len(a->ts) == 0){
        break;
      }
      TASKS_remove(a->ts, a->hlgt);
      ts_len = TASKS_len(a->ts);
      if(ts_len != 0 && a->hlgt >= ts_len){
        a->hlgt = ts_len - 1; 
      }
      break;
  }
  
  UTILS_render_tasks(a);
  UI_WINDOW_refresh(a->m_w); 
}

void UTILS_render_tasks(app_context_s* a_ctx){
  UI_WINDOW_s* w = a_ctx->m_w;
  UI_WINDOW_clear(w);
  TASKS_sl ts = a_ctx->ts;
  int hlgt = a_ctx->hlgt; 

  int col_w[] = {5, 36, 12, 12, 12, 12};

  // Print the table header
  attr_t attr = A_BOLD; 

  wattron(w->win, attr);
  mvwprintw(w->win, 1, 1, "%-*s%-*s%-*s%-*s%-*s%-*s",
            col_w[0], "ID",
            col_w[1], "NAME",
            col_w[2], "DURATION",
            col_w[3], "START",
            col_w[4], "ENDS",
            col_w[5], "DEPENDS");
  wattroff(w->win, attr);

  // Printing the rows
  for(int i=0; i<w->h; i++){
    task_s t = ts[i];

    char* name;
    char start_str[1024];
    char end_str[1024];
    int dur;
    char* dep_str;

    // Task name
    name = t.name;

    //Task start
    struct tm* ts = localtime(&t.start);
    strftime(start_str, sizeof(start_str), "%d/%m/%y", ts);

    // Task duration
    dur = (int)t.duration/86400.0;

    // Task end
    ts = localtime(&t.end);
    strftime(end_str, sizeof(end_str), "%d/%m/%y", ts);

    // Task depends
    dep_str = "HC";
   // TODO: Do real implementation 
    if(name == NULL){
      break;  
    }
    attr_t attr = i==hlgt ? A_UNDERLINE | A_BOLD | A_REVERSE : A_NORMAL; 
    wattron(w->win, attr);
    mvwprintw(w->win, i+2, 1, "%-*d%-*s%-*d%-*s%-*s%-*s",
              col_w[0], i,
              col_w[1], name,
              col_w[2], dur,
              col_w[3], start_str,
              col_w[4], end_str,
              col_w[5], dep_str);
    wattroff(w->win, attr);
  }
}
time_t UTILS_time_parse(char* time_str){
  struct tm tm_time;
  memset(&tm_time, 0, sizeof(struct tm));
  strptime(time_str, "%d/%m/%y", &tm_time);
  return mktime(&tm_time);
}
double UTILS_duration_parse(char* dur_str){
  double dur_days = strtol(dur_str, NULL, 10);
  return dur_days*24*60*60;
}
