/*HEADER********************************************************************
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* Comments:
*
*   This file contains the source for the TSS example program.
*
*END************************************************************************/
#include "TSS_API.h"
#include "freemaster.h"
#include "app_init.h"
#include "events.h"
#include "main.h"
#include "board.h"
#include "delay.h"
#include "i2c.h"
#include "mma8451.h"
#include "math.h"

uint16_t u16LPcounter = 0u;

/*********************** GUI - FreeMASTER TSA table ************************/

#if FMSTR_USE_TSA
  /* Example of FreeMASTER User Application Table */
  FMSTR_TSA_TABLE_BEGIN(UserAppTable)
    FMSTR_TSA_RW_VAR(u16LPcounter, FMSTR_TSA_UINT8)
  FMSTR_TSA_TABLE_END()

  /* FreeMASTER Global Table List definition */
  FMSTR_TSA_TABLE_LIST_BEGIN()
    #if TSS_USE_FREEMASTER_GUI
      FMSTR_TSA_TABLE(TSS_Table)
    #endif
    FMSTR_TSA_TABLE(UserAppTable)
  FMSTR_TSA_TABLE_LIST_END()
#endif

/**
 * \brief  Main function
 *
 * \param  void
 *
 * \return int
 */
int main (void)
{
  InitPorts();
  /* Default TSS init */
  TSS_Init_ASlider();
  /* Init PWM for LED control */
  PWM_init();
    /* Enable Interrupts globally */
	
  EnableInterrupts();
  /* Reset Low Power Counter flag */
  u16LPcounter = 0u;
	


	i2c_init();																/* init i2c	*/
	if (!init_mma()) {												/* init mma peripheral */
		
		while (1)																/* not able to initialize mma */
			;
	}
	Delay(1000);
	
  for(;;)
  {  
			//	SET_LED_RED(200);
			//	SET_LED_GREEN(200);
			//	SET_LED_BLUE(200);
   
		read_full_xyz();
		convert_xyz_to_roll_pitch();
		if(fabs(roll)>33 || fabs(pitch)>33){
			int c=0;
			while(c<=200){
				c=c+40;
				DelayMS(200);
				SET_LED_RED(c);
				SET_LED_GREEN(c);
				SET_LED_BLUE(c);

			}
			
				c=0;
			while(c<1000){
				DelayMS(10);	
				if (TSS_Task() == TSS_STATUS_OK)
    {

    }
		read_full_xyz();
		convert_xyz_to_roll_pitch();				
		if(fabs(roll)<33 && fabs(pitch)<33){
				break;
		}	c++;		
			}
					 c= 200;
			while(c<=0){
		c= c - 40 ;
		Delay(200);
		SET_LED_RED(c);
		SET_LED_GREEN(c);
		SET_LED_BLUE(c);
	}
		SET_LED_RED(0);
		SET_LED_GREEN(0);
		SET_LED_BLUE(0);			
		}	else{
				int c= 200;
			while(c<=0){
		c= c - 40 ;
		Delay(200);
		SET_LED_RED(c);
		SET_LED_GREEN(c);
		SET_LED_BLUE(c);
	}
		SET_LED_RED(0);
		SET_LED_GREEN(0);
		SET_LED_BLUE(0);
			
		}
    /* Write your code here ... */
  }
}
void DimLED(void){
	int c =200;
	while(c<=0){
		c= c - 40 ;
		Delay(200);
		SET_LED_RED(c);
		SET_LED_GREEN(c);
		SET_LED_BLUE(c);
	}
		SET_LED_RED(0);
		SET_LED_GREEN(0);
		SET_LED_BLUE(0);
}
