/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �߼����ƶ�ʱ����ʱ
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
#include "./tim/bsp_advance_tim.h"
#include "./led/bsp_led.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{

	LED_GPIO_Config();

  /* ��ʼ���߼����ƶ�ʱ����ʱ��1s����һ���ж� */
	TIMx_Configuration();
  
  while(1)
  {       
  }
}



/*********************************************END OF FILE**********************/

