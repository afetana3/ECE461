#include "main.h"

#define TPM_MODULE  3750
#define DUTY_MIN	220
#define DUTY_MAX	350

void set_pos(int angle);

int main(void)
{
	int counter = 0;
	char ch = 0;
	
	put("\r\nHello World! TPM Lab - PWM\r\n");
	
	PORTB_PCR0 = PORT_PCR_MUX(3);
	TPM_init_PWM(TPM1_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
	TPM_CH_init(TPM1_BASE_PTR, 0, TPM_PWM_H);
	set_TPM_CnV(TPM1_BASE_PTR, 0, DUTY_MIN);
	
	put("Press \"q\"/\"a\" to increase/decrease the angle of the Servo\r\n");
	
	while(TRUE)
	{
		ch = in_char();
		if(ch == 0x71)
		{
			if(counter<10)
			{
				put("Increasing\r\n");
				set_pos(++counter);
			}
		}
		else if (ch == 0x61)
		{
			if(counter>0)
			{
				put("Decreasing\r\n");
				set_pos(--counter);
			}
		}
		else
			put("\r\nNot valid Key\r\n");
	}
	return 0;
}

void set_pos(int angle)
{
	int duty = 0;
	duty = angle*((DUTY_MAX-DUTY_MIN)/10) + DUTY_MIN;
	set_TPM_CnV(TPM1_BASE_PTR, 0, duty);
}


