#ifndef TIMERS_H
#define TIMERS_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

	typedef struct Data{

      float pressao;
      uint16_t angulo;
      uint8_t alarm;
	} data;
 
		void interrupt4_OVF_Init();
		void serial();

	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif
