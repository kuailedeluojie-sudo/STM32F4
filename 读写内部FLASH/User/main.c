/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��STM32���ڲ�FLASHд������
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
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./internalFlash/bsp_internalFlash.h"   



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  /*��ʼ��USART������ģʽΪ 115200 8-N-1*/
  Debug_USART_Config();
	LED_GPIO_Config();
 
	LED_BLUE;
	/*����printf��������Ϊ�ض�����fputc��printf�����ݻ����������*/
  printf("this is a usart printf demo. \r\n");
	printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");	
	printf("���ڽ��ж�д�ڲ�FLASHʵ�飬�����ĵȴ�\r\n");
	
	if(InternalFlash_Test()==0)
	{
		LED_GREEN;
		printf("��д�ڲ�FLASH���Գɹ�\r\n");

	}
	else
	{
		printf("��д�ڲ�FLASH����ʧ��\r\n");
		LED_RED;
	}
	
	
  while(1)
	{	} 

}



/*********************************************END OF FILE**********************/

