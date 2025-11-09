#include "structs.h"
#include "tasks.h"
#include "ui_window.h"
#include "textbox.h"

typedef enum{
  DIALOG_TYPE_NULL,
  DIALOG_TYPE_ADD,
  DIALOG_TYPE_MODIFY
} DIALOG_type_e;

typedef enum{
  DIALOG_TEXTBOX_TASK = 0,
  DIALOG_TEXTBOX_START = 1,
  DIALOG_TEXTBOX_DURATION = 2, 
  DIALOG_TEXTBOX_END = 3,
  DIALOG_TEXTBOX_DEPENDS = 4
} DIALOG_active_tb_e;

typedef struct DIALOG_s {
  UI_WINDOW_s* win;
  TEXTBOX_s* task_tb;
  TEXTBOX_s* start_tb;
  TEXTBOX_s* duration_tb;
  TEXTBOX_s* end_tb;
  TEXTBOX_s* depends_tb;
  TEXTBOX_s**  tb_pl;
  DIALOG_active_tb_e active_tb;
  DIALOG_type_e type;
} DIALOG_s;

DIALOG_s  DIALOG_make();
void      DIALOG_alloc(DIALOG_s* d);
void      DIALOG_del(DIALOG_s* d);
void      DIALOG_draw(DIALOG_s* d);
void      DIALOG_show(DIALOG_s *d, app_context_s* a_ctx);
// Private functions
void      _DIALOG_active_textbox_cycle(DIALOG_s *d);
void      _DIALOG_content_set(DIALOG_s* d, task_s* t);
void      _DIALOG_content_clear(DIALOG_s* d);
void      _DIALOG_active_textbox_attr_update(DIALOG_s *d);
void      _DIALOG_textbox_enter(DIALOG_s* d, app_context_s* a_ctx);
void      _DIALOG_recalculate(DIALOG_s* d, app_context_s* a_ctx);
