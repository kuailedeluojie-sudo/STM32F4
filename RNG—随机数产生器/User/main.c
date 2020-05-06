/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ��RNG���������
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
#include "./usart/bsp_debug_usart.h"

static void Delay(__IO u32 nCount); 


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint8_t i;
	uint32_t random = 0;

	
	LED_GPIO_Config();
	
  /*��ʼ��USART������ģʽΪ 115200 8-N-1*/
  Debug_USART_Config(); 

	printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");	
	
	/* ʹ��RNGʱ�� */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	
	/* ʹ��RNG���� */
  RNG_Cmd(ENABLE);
	
  while(1)
	{		
		for(i = 0; i < 8; i++)
    {
      /* �ȴ������������� */
      while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
      {
      }

      /*��ȡ�����*/       
      random = RNG_GetRandomNumber();
			
			printf("\r\nRNG �������������0x%08x",random);

    }
		Delay(0xAFFFFFF);


	} 

}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/

