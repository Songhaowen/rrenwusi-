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
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	TIM3_PWM_Init(899,0);//不分频 pwm频率为80KHZ
	 
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


