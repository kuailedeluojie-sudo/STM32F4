/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڲ�FLASH�������ָ�ѡ���ֽ���Ĭ��ֵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
	
	
/*	
�� �������������裺

1.����ñ����ʵ�������BOOT0��BOOT1���Ŷ�ʹ����ñ���ӵ�3.3V
2.ʹ��DAP���������ر����򲢸�λ��Ȼ�����ĵȴ�����LED������ת�̣�����������2�������ң��ȴ���5���ӻ���ת��˵���ָ�ʧ�ܣ�
3.LED�Ʊ�Ϊ�̵ƺ󣬴������������س���STM32��FLASH(����ͨ����ˮ������)
4.�������޷����أ�������1-3���衣
5.���سɹ��󣬰�BOOT0��BOOT1���Ŷ�ʹ����ñ���ӵ�GND��
6.��λ�����壬�۲��µĳ����Ƿ�����(����ˮ������ʱ��LED�Ƿ�������˸)
7.��ɡ�	
*/	
	
	
	
	
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./internalFlash/internalFlash_reset.h"  


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
	Debug_USART_Config();	
	LED_BLUE;
	
	FLASH_INFO("�����򽫻ᱻ���ص�STM32���ڲ�SRAM���С�");
	FLASH_INFO("���س���ǰ����ȷ�ϰ�ʵ����BOOT0��BOOT1���Ŷ��ӵ�3.3V��Դ������");

	FLASH_INFO("\r\n");
	FLASH_INFO("----����һ��STM32оƬ�ڲ�FLASH��������----"); 
	FLASH_INFO("������оƬ���ڲ�FLASHѡ���ֽڻָ�ΪĬ��ֵ"); 
	
	
	#if 0 //���̵��ԡ���ʾʱʹ�ã��������ʱ����Ҫ���д˺���
	SetPCROP();	//�޸�PCROPλ������оƬ�����޷����س����ڲ�FLASH�Ļ���
	#endif
	
	#if 0  //���̵��ԡ���ʾʱʹ�ã��������ʱ����Ҫ���д˺���
	WriteProtect_Test(); //�޸�д����λ������оƬ���������ó�д�����ĵĻ���
	#endif

	OptionByte_Info();
	
	/*�ָ�ѡ���ֽڵ�Ĭ��ֵ���������*/
	if(InternalFlash_Reset()==FLASH_COMPLETE)
	{		
		FLASH_INFO("ѡ���ֽڻָ��ɹ������BOOT0��BOOT1���Ŷ����ӵ�GND��");
		FLASH_INFO("Ȼ�������һ����ͨ�ĳ������س���оƬ���ڲ�FLASH���в���"); 
		LED_GREEN;
	}	
	else
	{			
		FLASH_INFO("ѡ���ֽڻָ��ɹ�ʧ�ܣ��븴λ����");
		LED_RED;
	}

	OptionByte_Info();	

	while (1)
	{

	}
}


void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

