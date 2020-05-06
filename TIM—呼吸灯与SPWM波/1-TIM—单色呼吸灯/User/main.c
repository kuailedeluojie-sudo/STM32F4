/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����������
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
#include "./led/bsp_breath_led.h"
#include "./usart/bsp_debug_usart.h"



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{

  /*��ʼ������*/
  Debug_USART_Config();
 
	printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");		
	printf("\r\n ����������\r\n");	  
  printf("\r\n RGB LED �Ժ����Ƶ���ʽ��˸\r\n ");

  /* ��ʼ�������� */
	BreathLED_Config(); 
  
  while(1)
  {
  }

}


/*********************************************END OF FILE**********************/

