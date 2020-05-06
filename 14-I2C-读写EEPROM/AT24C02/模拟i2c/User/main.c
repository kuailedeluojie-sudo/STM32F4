/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��дEEPROM
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
#include "./i2c/bsP_i2c_ee.h"
#include "./led/bsp_led.h"



#define  EEP_Firstpage      0x00
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];
uint8_t I2C_Test(void);


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
  Debug_USART_Config(); 

	printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");		 

	printf("\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");

	if(ee_Test() == 1)
	{
		LED_GREEN;
	}
	else
	{
			LED_RED;
	}
  
  while (1)
  {      
  }  

}



/*********************************************END OF FILE**********************/

