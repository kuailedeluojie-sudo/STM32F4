/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.5.1�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./Bsp/beep/bsp_beep.h" 
#include "./Bsp/usart/bsp_debug_usart.h"
#include "./Bsp/systick/bsp_SysTick.h"
#include "./Bsp/TouchPad/bsp_touchpad.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* ��ʼ�������� */
	Beep_GPIO_Config();
	
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	
	/* ��ʼ��ϵͳ�δ�ʱ�� */
	SysTick_Init();

  /* ��ʼ�����ݰ��� */
	TPAD_Init();
	
	while(1)
	{
		if(TPAD_Scan(0))
		{
			BEEP_ON;
			Delay_ms(100);
			BEEP_OFF;
		}		
		Delay_ms(50);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
