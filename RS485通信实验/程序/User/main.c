/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   485ͨѶ����
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
#include "./485/bsp_485.h"
#include "./key/bsp_key.h" 

static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 

	char *pbuf;
	uint16_t len;
	
	LED_GPIO_Config();	
	
  /*��ʼ��USART1*/
  Debug_USART_Config();
	
	/*��ʼ��485ʹ�õĴ��ڣ�ʹ���ж�ģʽ����*/
	_485_Config();
	
	LED_BLUE;
	
	Key_GPIO_Config();
	
	printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");
  printf("\r\n Ұ��F429 485ͨѶʵ������\r\n");
	
	printf("\r\n ʵ�鲽�裺\r\n");

	printf("\r\n 1.ʹ�õ������Ӻ�����485ͨѶ�豸\r\n");
	printf("\r\n 2.ʹ������ñ���Ӻ�:3V3<--->CAN/485_3V3,485-Rx --- PD5,485-Tx ---PD6 \r\n");
	printf("\r\n 3.��ʹ������Ұ�𿪷������ʵ�飬�����������嶼���ر����򼴿ɡ�\r\n");
	printf("\r\n 4.׼���ú󣬰�������һ���������KEY1������ʹ��485���ⷢ��0-255������ \r\n");
	printf("\r\n 5.���������485���յ�256���ֽ����ݣ����������16������ʽ��ӡ������ \r\n");
	
  while(1)
  {
		/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			uint16_t i;
			
			LED_BLUE;
			
			_485_TX_EN();
			
			for(i=0;i<=0xff;i++)
			{
			_485_SendByte(i);	 //��������
			}
			
			/*�Ӷ�����ʱ����֤485�����������*/
			Delay(0xFFF);
			_485_RX_EN();
			
			LED_GREEN;
			
			printf("\r\n�������ݳɹ���\r\n"); //ʹ�õ��Դ��ڴ�ӡ������Ϣ���ն�

		}
		else
		{		
			LED_BLUE;
			
			pbuf = get_rebuff(&len);
			if(len>=256)
			{
				LED_GREEN;
				printf("\r\n���յ�����Ϊ%d������\r\n",len);	
				_485_DEBUG_ARRAY((uint8_t*)pbuf,len);
				clean_rebuff();
			}
		}
  }

}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/

