/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ¼����ط�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  *                              ͷ�ļ�
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "Bsp/usart/bsp_debug_usart.h"
#include "Bsp/systick/bsp_SysTick.h"
#include "Bsp/wm8978/bsp_wm8978.h" 
#include "Bsp/key/bsp_key.h" 
#include "Bsp/TouchPad/bsp_touchpad.h"
#include "App/Recorder.h"
#include "ff.h" 

/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
FATFS fs;											/* Work area (file system object) for logical drives */	
/**
  ******************************************************************************
  *                                ������
  ******************************************************************************
  */
/*
*********************************************************************************************************
* Description : ��ʼ��BL8782 wifiģ��ʹ�����ţ����ر�ʹ��
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
	FRESULT result; 
  
	/*  NVIC�ж����ȼ���ѡ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
	/* �ر�BL_8782wifiʹ�� */
	BL8782_PDN_INIT();
	
	/* ��ʼ������ */
	Key_GPIO_Config();
	
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	
	/* ����SD���ļ�ϵͳ */
	result = f_mount(&fs,"0:",1);  //�����ļ�ϵͳ
	if(result!=FR_OK)
	{
		printf("\n SD���ļ�ϵͳ����ʧ��\n");
		while(1);
	}
	
	/* ��ʼ��ϵͳ�δ�ʱ�� */
	SysTick_Init();	
	printf("WM8978¼���ͻطŹ���\n");

	/*  ��ʼ�����ݰ���  */
	TPAD_Init();	
	
	/* ���WM8978оƬ���˺������Զ�����CPU��GPIO */
	if (wm8978_Init()==0)
	{
		printf("��ⲻ��WM8978оƬ!!!\n");
		while (1);	/* ͣ�� */
	}
	printf("��ʼ��WM8978�ɹ�\n");	
	
	/* ¼����طŹ��� */
	RecorderDemo();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
