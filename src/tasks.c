#include "tasks.h"
#include <string.h>

TASKS_sl TASKS_make(){
  TASKS_sl ts = calloc(TASKS_MAX, sizeof(TASKS_sl)); 
  ts[0].name = NULL;
  return ts;
}

void TASKS_del(TASKS_sl ts){
  for(int i=0; i<TASKS_MAX; i++){
    char* task_name = ts[i].name;
    if(task_name != NULL){
     free(task_name); 
    }
  }
 free(ts);
}

int TASKS_add(TASKS_sl ts, int idx, char* name, time_t start, double duration){
  int num_tasks = TASKS_len(ts);

  if(num_tasks == TASKS_MAX){
    return -1;
  }
  // Ensure contiguity
  if(idx!=0 && ts[idx-1].name==NULL){ 
    return -1;
  }

  memmove(ts+idx+1, ts+idx, sizeof(task_s) * (num_tasks-idx + 1));
  ts[idx].id = idx; 
  ts[idx].name = malloc(strlen(name) + 1);
  strcpy(ts[idx].name, name);
  ts[idx].start = start;
  ts[idx].duration = duration;

  return 0;
}
int TASKS_len(TASKS_sl ts){
  for(int i=0; i<TASKS_MAX; i++){
    if(ts[i].name == NULL){
      return i;
    }
    // Case where all elements are full
    if(i==TASKS_MAX-1){ 
      return TASKS_MAX;
    }
  }
  return 0;
}
