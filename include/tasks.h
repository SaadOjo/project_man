#pragma once
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#define TASKS_MAX 256

typedef struct Task{
  int id;
  int fs_id;
  char* name;
  time_t start;
  double duration;
} Task;

Task* Tasks_make();
int Tasks_add(Task* ts, int id, char* name, time_t start, double duration);
int Tasks_len(Task* ts);
