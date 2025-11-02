#include "editable_text.h"
#include "structs.h"
#include "tasks.h"
#include "ui_window.h"

typedef enum{
  DIALOG_TYPE_NULL,
  DIALOG_TYPE_ADD,
  DIALOG_TYPE_MODIFY
} DIALOG_type_e;

typedef enum{
  DIALOG_TEXTBOX_TASK,
  DIALOG_TEXTBOX_DURATION,
  DIALOG_TEXTBOX_START,
  DIALOG_TEXTBOX_END,
  DIALOG_TEXTBOX_DEPENDS
} DIALOG_textbox_e;

typedef struct DIALOG_contents_s{
  EDITABLE_TEXT_s* task;
  EDITABLE_TEXT_s* duration;
  EDITABLE_TEXT_s* start;
  EDITABLE_TEXT_s* end;
  EDITABLE_TEXT_s* depends;
} DIALOG_contents_s;

typedef struct DIALOG_s {
  UI_WINDOW_s* win;
  DIALOG_contents_s* contents;
  DIALOG_textbox_e active_textbox;  
  DIALOG_type_e type;
} DIALOG_s;

DIALOG_s  DIALOG_make();
void      DIALOG_alloc(DIALOG_s* d);
void      DIALOG_del(DIALOG_s* d);
void      DIALOG_draw(DIALOG_s* d);
void      DIALOG_navigate(DIALOG_s *d, app_context_s* a_ctx);
// Private functions
void      _DIALOG_active_textbox_cycle(DIALOG_s *d);
void      _DIALOG_dialog_content_set(DIALOG_s* d, task_s* t);
