/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �߼����ƶ�ʱ���������
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
#include "./key/bsp_key.h" 

extern uint16_t aSRC_Buffer[3];
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{
	/* ��ʼ������GPIO */
  Key_GPIO_Config();
	
  /* ��ʼ���߼����ƶ�ʱ��������PWMģʽ��ʹ��ͨ��1������� */
	TIMx_Configuration();
  
  while(1)
  {       
		/* ɨ��KEY1 */
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			aSRC_Buffer[0]=64;
			aSRC_Buffer[2]=511;
		}   
    /* ɨ��KEY2 */
    if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			aSRC_Buffer[0]=383;
			aSRC_Buffer[2]=127;
		}   
  }
}



/*********************************************END OF FILE**********************/

