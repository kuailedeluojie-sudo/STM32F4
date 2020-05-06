/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��дSDRAM
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
#include "./sdram/bsp_sdram.h"
#include <stdlib.h>


void Delay(__IO u32 nCount); 

/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
    
  /* ��ʼ������ */
  Debug_USART_Config();
  
  printf("\r\n Ұ��STM32F429 SDRAM ��д��������\r\n");
  
  /*��ʼ��SDRAMģ��*/
  SDRAM_Init();
  
  /*����������ʾ���ڶ�дSDRAM����*/
  LED_BLUE;
  
  /*��SDRAM���ж�д���ԣ����SDRAM�Ƿ�����*/
  if(SDRAM_Test()==1)
  {
		//�������� �̵���
    LED_GREEN;			  
  }
	else
	{
		//����ʧ�� �����
		LED_RED;
	}
	
	/*ָ�뷽ʽ����SDRAM*/
	{	
	 uint32_t temp;
	
	 printf("\r\nָ�뷽ʽ����SDRAM\r\n");
	/*��SDRAMд��8λ����*/
	 *( uint8_t*) (SDRAM_BANK_ADDR ) = (uint8_t)0xAA;
	 printf("\r\nָ�����SDRAM��д������0xAA \r\n");

	 /*��SDRAM��ȡ����*/
	 temp =  *( uint8_t*) (SDRAM_BANK_ADDR );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);

	 /*д/�� 16λ����*/
	 *( uint16_t*) (SDRAM_BANK_ADDR+10 ) = (uint16_t)0xBBBB;
	 printf("ָ�����SDRAM��д������0xBBBB \r\n");
	 
	 temp =  *( uint16_t*) (SDRAM_BANK_ADDR+10 );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);


	 /*д/�� 32λ����*/
	 *( uint32_t*) (SDRAM_BANK_ADDR+20 ) = (uint32_t)0xCCCCCCCC;
	 printf("ָ�����SDRAM��д������0xCCCCCCCC \r\n");	 
	 temp =  *( uint32_t*) (SDRAM_BANK_ADDR+20 );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);

	}
	
	/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
	{
		testValue = 0xDD;
		printf("\r\n���Զ�λ����SDRAM��д������0xDD,��������0x%X,������ַΪ%X\r\n",testValue,(uint32_t )&testValue);	 
	}
	
	

  while(1); 
 

}


void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

