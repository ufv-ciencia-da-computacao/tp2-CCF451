#ifndef __TIME_H__
#define __TIME_H__

typedef struct time * time_t;

void time_init(time_t *time);
void time_tick(time_t *time);
int  time_now(time_t *time);

#endif