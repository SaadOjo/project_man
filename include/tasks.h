#pragma once
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#define TASKS_MAX 256

typedef struct task_sl{
  int id;
  int fs_id;
  char* name;
  time_t start;
  double duration;
} *tasks_sl;

tasks_sl TASKS_make();
int TASKS_add(tasks_sl ts, int id, char* name, time_t start, double duration);
int TASKS_len(tasks_sl ts);
