#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 

 int main(void)
 {		
	 u16 a=1;
   u8 b=0;
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TIM3_PWM_Init(899,0);//����Ƶ pwmƵ��Ϊ80KHZ
	 
  while(1)
	{
		delay_ms(10);
		if(b)
			a++;
		else
			a--;
		
    if(a>300)
      b=0;
    if(a==0)
      b=1;

    TIM_SetCompare2(TIM3,a);
	}		
		
			
 
}	 


