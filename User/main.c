#include "system.h"
#include "led.h"
#include  "SysTick.h"
#include "beep.h"
#include "key/key.h"
#include "exti/exti.h"
#include "time/time.h"
#include "pwm/pwm.h"
#include "usart.h"
/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������ͨ��whileѭ��ռ��CPU���ﵽ��ʱ����
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay(u32 i)
{
	while(i--);
}

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	u8 key,i=0;
	u16 j=0;
	u8 fx=0;
	u16 len=0;
	u16 t=0;
	SysTick_Init(72);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
//	My_EXTI_Init();  //�ⲿ�жϳ�ʼ��
	TIM4_Init(10000,36000-1);  //500ms
	TIM3_CH2_PWM_Init(200,72-1);
	USART1_Init(115200);
	while(1)
	{
		if(fx==0)
		{
			j++;
			if(j==300)
			{
				fx=1;
			}
		}
		else
		{
			j--;
			if(j==0)
			{
				fx=0;
			}
		}
		TIM_SetCompare2(TIM3,j);
		if(USART1_RX_STA&0x8000)
		{
			len = USART1_RX_STA&0x3fff;
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART1_RX_BUF[t]);         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			USART1_RX_STA=0;
		}
		
//		key = KEY_Scan(0);
//		switch(key)
//		{
//			case KEY0_PRESS:
//			{
//				LED1=0;
//				break;
//			}
//			case KEY1_PRESS:
//			{
//				LED1=1;
//				break;
//			}
//			case KEY2_PRESS:
//			{
//				LED1=0;
//				break;
//			}
//			case KEY_UP_PRESS:
//			{
//				LED1=1;
//				break;
//			}
//		}
		delay_ms(10);
//		LED1=!LED1;
//		delay_ms(20);
//		LED2=!LED2;
//		BEEP = !BEEP;
//		delay_ms(200);
//		GPIO_ResetBits(LED1_PORT,LED1_PIN);//����DS0
//		delay(6000000);
//		GPIO_SetBits(LED1_PORT,LED1_PIN);
//		delay(6000000);
	}
}
