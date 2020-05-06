/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SDIO sd������ʵ�飨�����ļ�ϵͳ����
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
#include "usart/bsp_debug_usart.h"
#include "sdio/sdio_test.h"
#include "led/bsp_led.h"
#include "key/bsp_key.h" 


/**
	*********************************************************************************************************
	* Description : ��ʼ��BL8782 WiFiģ��ʹ�����ţ�������WiFiģ��
	* Argument(s) : none.
	* Return(s)   : none.
	*********************************************************************************************************
	*/
static void BL8782_PDN_INIT(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOB, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);  //����WiFiģ��
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /* ����WiFiģ�� */
	BL8782_PDN_INIT();
	
	/* ��ʼ��LED�� */
  LED_GPIO_Config();
	LED_BLUE;	
	/* ��ʼ���������� */
	Key_GPIO_Config();
  
  /*��ʼ��USART1*/
  Debug_USART_Config();
  
	printf("\r\n��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");	
	
	printf("�ڿ�ʼ����SD����������ǰ��������������32G���ڵ�SD��\r\n");			
	printf("��������SD������ ���ļ�ϵͳ ��ʽ��д����ɾ��SD�����ļ�ϵͳ\r\n");		
	printf("ʵ����ͨ�����Ը�ʽ����ʹ��SD���ļ�ϵͳ�����ָ̻�SD���ļ�ϵͳ\r\n");		
	printf("\r\n ��sd���ڵ�ԭ�ļ����ɻָ���ʵ��ǰ��ر���SD���ڵ�ԭ�ļ�������\r\n");		
	
	printf("\r\n ����ȷ�ϣ��밴�������KEY1��������ʼSD������ʵ��....\r\n");	
  
  /* Infinite loop */
  while (1)
  {	
		/*���°�����ʼ����SD����дʵ�飬����SD��ԭ�ļ�*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			printf("\r\n��ʼ����SD����дʵ��\r\n");	
		  SD_Test();			
		}
	} 
}

/*********************************************END OF FILE**********************/

