#pragma once
#include "tasks.h"
typedef struct UI_WINDOW_s UI_WINDOW_s;

typedef enum{
  MODAL_STATE_ON,
  MODAL_STATE_OFF
} modal_state_e;

typedef struct app_context_s{
  UI_WINDOW_s* m_w; //Modal window
  UI_WINDOW_s* d_w; //Dialog window
  TASKS_sl ts;
  modal_state_e s;
  int hlgt;
} app_context_s;

