#include "config.h"
#include "struct.h"
#include <stdio.h>
#include <time.h>


int set_start_time(struct time *s){
s->start_time = time(NULL);
return 0;
}

int set_end_time(struct time *s){
s->end_time = time(NULL);
return 0;
}

int get_sleeptime(struct time *s){
  int time_to_sleep = PERIODE_TIME - (s->end_time - s->start_time);
  if (time_to_sleep < 0){
    return 0;
  }
  else
  {
    return time_to_sleep;
  }
}
