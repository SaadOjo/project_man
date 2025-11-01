#pragma once
#include "structs.h"

void UTILS_ui_init();
app_context_s UTILS_app_context_make();
void UTILS_navigate(app_context_s* a, int ch);
void UTILS_render_tasks(app_context_s* a_ctx);
