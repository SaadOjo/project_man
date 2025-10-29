#pragma once
#include "tasks.h"
typedef struct UI_window_s UI_window_s;

typedef enum{
  MODAL_STATE_ON,
  MODAL_STATE_OFF
} modal_state_e;

typedef struct app_context_s{
  UI_window_s* m_w; //Modal window
  UI_window_s* d_w; //Dialog window
  tasks_sl ts;
  int hlgt;
} app_context_s;

