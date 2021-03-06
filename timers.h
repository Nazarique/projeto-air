#ifndef TIMERS_H
#define TIMERS_H

#include "bibliotecas.h"

#ifdef __cplusplus

extern "C"{
#endif

typedef struct Data{

	int16_t pressao;
	uint16_t angulo;
	uint8_t alarm;
} data;

typedef struct
{
	uint32_t timer_start;
	uint32_t timer_interval;
} system_timer;

extern uint8_t flag_control_stat_machine;
extern system_timer watch_insp;
extern system_timer watch_exp;

extern system_timer timer_dead_time;
extern system_timer timer_periodo_rampa;
extern system_timer timer_ocioso;

void interrupt4_OVF_Init();
void timer_set(system_timer *timer, uint32_t interval);
void timer_reset(system_timer *timer);
uint8_t timer_expired(system_timer *timer);
void watch_set(system_timer *timer);
uint32_t watch_get(system_timer *timer);
uint32_t get_global_counter();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
