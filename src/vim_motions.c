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

  string+=cur_idx;
  int len = strlen(string);
  int ws_obs = 0;
  for(int i = 0; i < len; i++){
   if(!ws_obs){
      ws_obs = string[i] == ' ' ? 1 : 0;
      continue;
    } 
    if(ws_obs && string[i] != ' '){
     return cur_idx + i; 
    }
  }
  return cur_idx; 
}
int vim_b(char* string, int cur_idx){
  
  int ws_obs = 0;
  int ch_obs = 0;
  int ch;

  if(cur_idx == 0){
    return 0;
  }

  if(string[cur_idx - 1] == ' '){
    cur_idx--;
  }

  for(int i = cur_idx; i >= 0; i--){
    ch = string[i];

    if(ch != ' '){
      ch_obs = 1;
    }else if(ch_obs){
      ws_obs = 1;
    }

    if (ws_obs && ch_obs){
      return i + 1;
    }
    if(!ws_obs && i == 0){ // Case where cursor starts middle of first word with no pre-space
     return 0; 
    }
  }
  return 0;
}
int vim_e(char* string, int cur_idx){
  int len = strlen(string + cur_idx);

  int wb_obs = 0;
  int ch_obs = 0;
  
  int ch;

  if(len == 0){ // Cursor is end of string
    return cur_idx;
  }

  if(string[cur_idx + 1] == ' '){
    cur_idx++;
    len--;
  }
  for(int i = 0; i <= len; i++){
    ch = string[cur_idx + i];
  if (ch != ' '){
      ch_obs = 1;
    } else if (ch_obs) {
      wb_obs = 1; 
    }  
   if(ch_obs && wb_obs){
      return cur_idx + i - 1;
    }
  }
  return cur_idx + len - 1;
}

