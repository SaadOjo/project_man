#include <stdlib.h>
#include "editable_text.h"

#define EDITABLE_TEXT_MAX_LEN 1024  

EDITABLE_TEXT_s EDITABLE_TEXT_make(){
  EDITABLE_TEXT_s et;
  et.text = NULL;
  et.cursor = 0;
  return et;
}

void EDITABLE_TEXT_alloc(EDITABLE_TEXT_s* et){
  et->text = malloc(sizeof(char)*EDITABLE_TEXT_MAX_LEN);  
  et->text[0] = '\n';
}
void EDITABLE_TEXT_del(EDITABLE_TEXT_s* et){

}
