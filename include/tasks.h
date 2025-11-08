#pragma once
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#define TASKS_MAX 256

typedef struct task_s{
  int id;
  int fs_id;
  char* name;
  time_t start;
  double duration;
} task_s;

typedef task_s *TASKS_sl;

TASKS_sl TASKS_make();
void TASKS_del(TASKS_sl ts);

int TASKS_len(TASKS_sl ts);
void TASKS_add(TASKS_sl ts, int idx, char* name, time_t start, double duration);
void TASKS_modify(TASKS_sl ts, int idx, char* name, time_t start, double duration);
void TASKS_remove(TASKS_sl ts, int idx);
