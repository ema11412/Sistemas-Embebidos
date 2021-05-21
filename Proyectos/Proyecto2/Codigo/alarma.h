#ifndef INCLUDE_ALARMA_H_
#define INCLUDE_ALARMA_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
} hour_t;

hour_t hour;
hour_t alarm;

void
init_hour_type(hour_t* el)
{
  el->seconds = 0;
  el->minutes = 0;
  el->seconds = 0;
}

void
tick_min(hour_t* el)
{
  el->minutes++;
  if (el->minutes == 60)
  {
    el->hours++;
    el->minutes = 0;
    if (el->hours == 24)
    {
      el->hours = 0;
    }
  }
}

void
tick_hour(hour_t* el)
{
  el->hours++;
  if (el->hours == 24)
  {
    el->hours = 0;
  }
}

void
tick(hour_t* el)
{
  /* increase on each call by 1 second */
  el->seconds++;
  if (el->seconds == 60)
  {
    el->minutes++;
    el->seconds = 0;
    if (el->minutes == 60)
    {
      el->hours++;
      el->minutes = 0;
      if (el->hours == 24)
      {
        el->hours = 0;
      }
    }
  }
}

bool
hora_equals(hour_t* a, hour_t* b)
{
  return
      a->seconds == b->seconds &&
      a->minutes == b->minutes &&
      a->hours == b->hours;
}


#endif /* INCLUDE_ALARMA_H_ */
