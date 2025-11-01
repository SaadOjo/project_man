#pragma once

typedef enum {
   EDITABLE_TEXT_CURSOR_STATE_NORMAL, 
   EDITABLE_TEXT_CURSOR_STATE_INSERT
} EDITABLE_TEXT_cursor_state;
typedef struct EDITABLE_TEXT_s{
  char* text;
  int cursor;
} EDITABLE_TEXT_s;

EDITABLE_TEXT_s EDITABLE_TEXT_make();
void            EDITABLE_TEXT_alloc(EDITABLE_TEXT_s* et);
void            EDITABLE_TEXT_del(EDITABLE_TEXT_s* et);
