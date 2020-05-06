/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��ʾʹ��DMA���д��ڴ���
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
#include "./usart/bsp_usart_dma.h"
#include "./led/bsp_led.h"


extern uint8_t SendBuff[SENDBUFF_SIZE];
static void Delay(__IO u32 nCount); 


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  uint16_t i;
  /* ��ʼ��USART */
  Debug_USART_Config(); 

  /* ����ʹ��DMAģʽ */
  USART_DMA_Config();
  
  /* ����RGB��ɫ�� */
  LED_GPIO_Config();

  printf("\r\n USART1 DMA TX ���� \r\n");
  
  /*��佫Ҫ���͵�����*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'A';
    
  }

  /*Ϊ��ʾDMA�������ж�CPU���ܴ����������飬����ʹ��DMA�������ݣ����ǳ���
  *��ʱ�����п��ܻᵼ�µ��Զ˴��ڵ������ֻῨ��������ҷɵ������
  *���DMA�����е�ѭ��ģʽ��Ϊ����ģʽ*/		
  
  /* USART1 �� DMA����TX���� */
  USART_DMACmd(DEBUG_USART, USART_DMAReq_Tx, ENABLE);

  /* ��ʱCPU�ǿ��еģ����Ը����������� */  
  //����ͬʱ����LED
  while(1)
  {
    LED1_TOGGLE
    Delay(0xFFFFF);
  }
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/

