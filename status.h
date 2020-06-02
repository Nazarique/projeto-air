#ifndef STATUS_H
#define STATUS_H

	#ifdef __cplusplus
		extern "C"{
	#endif

	typedef struct 
	{
	    uint8_t  c_stop :1;
	    uint8_t  c_direcao; 

	    uint16_t c_angulo_final;
	    uint16_t c_angulo_inicial;

	    uint8_t  c_pressao_PEEP;

	    uint8_t  c_pwm_requerido;
	    uint8_t  c_pwm_insp;
	    uint8_t  c_pwm_atual;
	  } control_t;
	
	typedef struct
	{
		uint8_t   s_respirador;
		control_t s_control;
	} system_status;


	system_status *get_sys_status();
	void *set_sys_status(uint8_t status);
	void *set_control_angulo(uint16_t angulo);
	void *set_control_pwm(uint8_t pwm);
	void *set_control_PEEP(uint8_t peep);

	#ifdef __cplusplus
		} // extern "C"
	#endif

#endif
