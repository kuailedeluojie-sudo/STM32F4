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

extern __IO uint16_t ChannelPulse;
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
			/* ����ռ�ձ� */
			if(ChannelPulse<960)
				ChannelPulse+=64;
			else
				ChannelPulse=1024;
			TIM_SetCompare1(ADVANCE_TIM,ChannelPulse);
		}   
    /* ɨ��KEY2 */
    if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			/* ��Сռ�ձ� */
			if(ChannelPulse>=64)
				ChannelPulse-=64;
			else
				ChannelPulse=0;
			TIM_SetCompare1(ADVANCE_TIM,ChannelPulse);
		}   
  }
}



/*********************************************END OF FILE**********************/

