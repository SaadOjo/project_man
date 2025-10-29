#pragma once
#include "tasks.h"
typedef struct UI_Window UI_Window;

typedef struct App_context{
  UI_Window* m_w;
  Task* ts;
  int hlgt;
} App_context;

