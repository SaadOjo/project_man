#include <string.h>
#include "vim_motions.h"

int vim_l(char* string, int cur_idx){
int l = strlen(string);
  if(cur_idx>=(l-1)){
    return l-1;
  }
  return ++cur_idx;
}

int vim_h(char* string, int cur_idx){
  if(cur_idx == 0){
    return 0;
  }
  return --cur_idx;
}
int vim_w(char* string, int cur_idx){
  return cur_idx; 
}
int vim_b(char* string, int cur_idx){
  return cur_idx;
}
