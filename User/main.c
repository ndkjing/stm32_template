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
* 函 数 名         : delay
* 函数功能		   : 延时函数，通过while循环占用CPU，达到延时功能
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay(u32 i)
{
	while(i--);
}

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
//	My_EXTI_Init();  //外部中断初始化
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
				USART_SendData(USART1, USART1_RX_BUF[t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
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
//		GPIO_ResetBits(LED1_PORT,LED1_PIN);//点亮DS0
//		delay(6000000);
//		GPIO_SetBits(LED1_PORT,LED1_PIN);
//		delay(6000000);
	}
}
