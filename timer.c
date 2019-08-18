#include "timer.h"
#include "led.h"



void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period=arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler=psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //���TIMx�����жϱ�־ 
		LED1=!LED1;
		}
}

 void TIM3_PWM_Init(u16 arr,u16 psc)
 {
	     GPIO_InitTypeDef  GPIO_InitStructure;
       TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
       TIM_OCInitTypeDef TIM_OCInitTypeStrue;
	 
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	 
	  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	 
	 	//��ʱ��TIM3��ʼ��
	  TIM_TimeBaseStructure.TIM_Period= arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	  TIM_TimeBaseStructure.TIM_Prescaler=psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	 
	  TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM2;
	  TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCPolarity_High;
	  TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable;
	  TIM_OC2Init(TIM3,&TIM_OCInitTypeStrue);
	 
	  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	 
	  TIM_Cmd(TIM3,ENABLE);
 }










