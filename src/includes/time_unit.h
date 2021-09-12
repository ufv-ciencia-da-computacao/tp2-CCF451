#ifndef __TIME_UNIT_H__
#define __TIME_UNIT_H__

typedef int time_unit_t;

void time_unit_init(time_unit_t *time);
void time_unit_tick(time_unit_t *time);
int  time_unit_get(time_unit_t *time);

#endif
