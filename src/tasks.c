#include "tasks.h"

tasks_sl TASKS_make(){
  tasks_sl ts = calloc(TASKS_MAX, sizeof(tasks_sl)); 
  ts[0].name = NULL;
  return ts;
}

int TASKS_add(tasks_sl ts, int id, char* name, time_t start, double duration){
  for(int i=0; i<TASKS_MAX-1; i++){ //Check only for until last - 1 element, becase if last is already filled, cannot add new tasks
    if(ts[i].name == NULL){
      ts[i+1].name = NULL; //Mark next empty Task
      ts[i].id = id; 
      ts[i].name = malloc(strlen(name) + 1);
      strcpy(ts[i].name, name);
      ts[i].start = start;
      ts[i].duration = duration;
      break;
    }
  }
  return 0;
}
int TASKS_len(tasks_sl ts){
  for(int i=0; i<TASKS_MAX; i++){
    if(ts[i].name == NULL){
      return i;
    }
  }
  return 0;
}
