typedef struct 
{
  struct 
  {
    uint8_t flag_degrau :1;
    uint8_t direcao     :1;
    uint8_t pwm_requerido;
    uint8_t pwm_atual;
  } motor;

  struct 
  {
    uint16_t config;
    uint16_t init;
  } posicao;
} control_t;


volatile control_t control;

void degrauTime_Isr()                                                      
{
  static unsigned char cont = 1;

  if(control.motor.flag_degrau)
  {
    if(--cont==0)                                                           
    { 
    	cont = 1;                                            
    	control.motor.flag_degrau = 0;                                                                                                              
    }
  }
}

void degrau(uint8_t pwm, uint8_t pwm_atual)
{
  control.motor.flag_degrau = 1;

	if(pwm_atual == pwm)
	{
		return pwm_atual;
	}
	else if(pwm_atual > pwm)
	{
		pwm_atual--;
	}
	else if(pwm_Atual < pwm)
	{
		pwm_atual++;
	}
  return pwm_atual;
}

void set_Degrau()
{
  if(!control.motor.flag_degrau)
    {
      control.motor.pwm_atual = degrau(control.motor.pwm_requerido, control.motor.pwm_atual);
    }
  set_Duty(control.motor.pwm_atual); 
}

void inverte_Rotacao()
{
   volatile uint16_t posicao_encoder = 0;
   
   posicao_encoder = read_Posicao();

  if (posicao_encoder > control.posicao.init && control.motor.direcao == 1)
  {
    control.motor.direcao = 0;
    direct_Motor(control.motor.direcao)
  } 

  if (posicao_encoder < control.posicao.config && control.motor.direcao == 0) 
  {
    control.motor.direcao = 1;
    direct_Motor(control.motor.direcao);
  }
  set_Degrau(); 
}