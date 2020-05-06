/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SCT�ļ�Ӧ�á����Զ����������SDRAMʵ��
	
	* @note 	 -�������޸��������ļ���sct�ļ�!!
	*					 -������ʹ���ֶ���д��sct�ļ����ƴ洢������
	*					 ��ʾ����Զ����������SDRAM
	*					 ��ʾ���ʹ��malloc����SDRAM�ռ�
	*   
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

//���ñ������嵽��EXRAM�������ĺ�
#define __EXRAM  __attribute__ ((section ("EXRAM")))


//���������SDRAM
uint32_t testValue __EXRAM =7 ;
//��������Ч�ڣ�
//uint32_t testValue  __attribute__ ((section ("EXRAM"))) =7 ;

//���������SRAM
uint32_t testValue2  =7 ;



//�������鵽SDRAM
uint8_t testGrup[3] __EXRAM ={1,2,3};
//�������鵽SRAM
uint8_t testGrup2[3] ={1,2,3};




/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint32_t inerTestValue =10;
	  /*SDRAM_Init�Ѿ��������ļ���Reset_handler�е��ã�����main֮ǰ�Ѿ���ɳ�ʼ��*/
  //  SDRAM_Init();
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
    
  /* ��ʼ������ */
  Debug_USART_Config();
  
  printf("\r\nSCT�ļ�Ӧ�á����Զ����������SDRAMʵ��\r\n");
  
	printf("\r\nʹ�á�	uint32_t inerTestValue =10; ����䶨��ľֲ�������\r\n");
	printf("��������ĵ�ַΪ��0x%x,����ֵΪ��%d\r\n",(uint32_t)&inerTestValue,inerTestValue);
	
  printf("\r\nʹ�á�uint32_t testValue __EXRAM =7 ;����䶨���ȫ�ֱ�����\r\n");
	printf("��������ĵ�ַΪ��0x%x,����ֵΪ��%d\r\n",(uint32_t)&testValue,testValue);
	
  printf("\r\nʹ�á�uint32_t testValue2  =7 ; ����䶨���ȫ�ֱ�����\r\n");
	printf("��������ĵ�ַΪ��0x%x,����ֵΪ��%d\r\n",(uint32_t)&testValue2,testValue2);
	
	
	printf("\r\nʹ�á�uint8_t testGrup[3] __EXRAM ={1,2,3};����䶨���ȫ�����飺\r\n");
	printf("��������ĵ�ַΪ��0x%x,����ֵΪ��%d,%d,%d\r\n",(uint32_t)&testGrup,testGrup[0],testGrup[1],testGrup[2]);
	
  printf("\r\nʹ�á�uint8_t testGrup2[3] ={1,2,3};����䶨���ȫ�����飺\r\n");
	printf("��������ĵ�ַΪ��0x%x,����ֵΪ��%d��%d,%d\r\n",(uint32_t)&testGrup2,testGrup2[0],testGrup2[1],testGrup2[2]);
	
	
	/*ʹ��malloc��SDRAM�з���ռ�*/
	uint32_t *pointer = (uint32_t*)malloc(sizeof(uint32_t)*3); 	

	if(pointer != NULL)
	{
		*(pointer)=1;
		*(++pointer)=2;
		*(++pointer)=3;	
		
		printf("\r\nʹ�á�	uint32_t *pointer = (uint32_t*)malloc(sizeof(uint32_t)*3); ����̬����ı���\r\n");
		printf("\r\n�����Ĳ���Ϊ��\r\n*(pointer++)=1;\r\n*(pointer++)=2;\r\n*pointer=3;\r\n\r\n");
		printf("��������������ĵ�ַΪ��0x%x,�鿴����ֵ������\r\n",(uint32_t)pointer); 
		printf("*(pointer--)=%d, \r\n",*(pointer--));
		printf("*(pointer--)=%d, \r\n",*(pointer--));
		printf("*(pointer)=%d, \r\n",*(pointer));
		
		free(pointer);
	}
	else
	{
		printf("\r\nʹ��malloc��̬���������������\r\n");	
	}

  /*������*/
  LED_BLUE; 
	

  while(1); 
 

}


void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

