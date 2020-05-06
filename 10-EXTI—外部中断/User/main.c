/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ���ⲿ�ж�EXTI��ⰴ�������Ʋʵơ�
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
#include "./key/bsp_exti.h"

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
  	
	/* ��ʼ��EXTI�жϣ����°����ᴥ���жϣ�
  *  �����жϻ����stm32f4xx_it.c�ļ��еĺ���
	*  KEY1_IRQHandler��KEY2_IRQHandler�������жϣ���תLED�ơ�
	*/
	EXTI_Key_Config(); 
	
	/* �ȴ��жϣ�����ʹ���жϷ�ʽ��CPU������ѯ���� */
	while(1)                            
	{
	}
}



/*********************************************END OF FILE**********************/

