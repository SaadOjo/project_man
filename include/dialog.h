#include "structs.h"
#include "tasks.h"
#include "ui_window.h"
#include "textbox.h"

typedef enum{
  DIALOG_TYPE_NULL,
  DIALOG_TYPE_ADD,
  DIALOG_TYPE_MODIFY
} DIALOG_type_e;

typedef struct DIALOG_s {
  UI_WINDOW_s* win;
  TEXTBOX_s* task_tb;
  TEXTBOX_s* duration_tb;
  TEXTBOX_s* start_tb;
  TEXTBOX_s* end_tb;
  TEXTBOX_s* depends_tb;
  TEXTBOX_s**  tb_pl;
  int active_tb_idx;
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
