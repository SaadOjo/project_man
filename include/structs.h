#pragma once
#include "tasks.h"

typedef struct UI_WINDOW_s UI_WINDOW_s;
typedef struct DIALOG_s DIALOG_s;
typedef struct STATUSBAR_s STATUSBAR_s;

typedef struct app_context_s{
  UI_WINDOW_s* m_w; // Main window
  STATUSBAR_s* sb;
  DIALOG_s* d;
  TASKS_sl ts;
  int hlgt;
} app_context_s;

