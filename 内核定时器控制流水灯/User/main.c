/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   ʹ��DWT���о�ȷ��ʱ
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
#include "./led/bsp_led.h"
#include "./dwt_delay/core_delay.h"   


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
 
  /* ��ʼ���ں˶�ʱ�� */
	CPU_TS_TmrInit();
  
	while(1)
	{

		LED_RED; 
	  Delay_us(100000);    	// 10000 * 10us = 1000ms
		//Delay_ms(1000);
	  
		LED_GREEN;
	  Delay_us(100000);		// 10000 * 10us = 1000ms
		//Delay_ms(1000);
	
		LED_BLUE;
	  Delay_us(100000);		// 10000 * 10us = 1000ms
		//Delay_ms(1000);


	}   
}



/*********************************************END OF FILE**********************/

