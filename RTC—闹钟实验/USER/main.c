/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   RTC����
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
#include "./Bsp/led/bsp_led.h" 
#include "./Bsp/usart/bsp_debug_usart.h"
#include "./Bsp/RTC/bsp_rtc.h"
#include "./Bsp/lcd/bsp_lcd.h"
#include "./Bsp/beep/bsp_beep.h"


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{  
	/* ��ʼ��LED */
	LED_GPIO_Config();
	BEEP_GPIO_Config();

	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	printf("\n\r����һ��RTC����ʵ�� \r\n");
	
	/*=========================Һ����ʼ����ʼ===============================*/
	LCD_Init();
  LCD_LayerInit();
  LTDC_Cmd(ENABLE);
	
	/*�ѱ�����ˢ��ɫ*/
  LCD_SetLayer(LCD_BACKGROUND_LAYER);  
	LCD_Clear(LCD_COLOR_BLACK);
	
  /*��ʼ����Ĭ��ʹ��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
  LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BLACK);
	/*����LCD_SetLayer(LCD_FOREGROUND_LAYER)������
	����Һ����������ǰ����ˢ�£��������µ��ù�LCD_SetLayer�������ñ�����*/		
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
  /*=========================Һ����ʼ������===============================*/
	
	/*
	 * ���������ù�RTCʱ��֮��������ݼĴ���0д��һ�����������
	 * ����ÿ�γ����������е�ʱ���ͨ����ⱸ�ݼĴ���0��ֵ���ж�
	 * RTC �Ƿ��Ѿ����ù���������ù��Ǿͼ������У����û�����ù�
	 * �ͳ�ʼ��RTC������RTC��ʱ�䡣
	 */
  
  /* RTC���ã�ѡ��ʱ��Դ������RTC_CLK�ķ�Ƶϵ�� */
  RTC_CLK_Config();
   
  if (RTC_ReadBackupRegister(RTC_BKP_DRX) != RTC_BKP_DATA)
  {		
		/* �������� */
		RTC_AlarmSet();
		
    /* ����ʱ������� */
		RTC_TimeAndDate_Set();
		

  }
  else
  {
    /* ����Ƿ��Դ��λ */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n ������Դ��λ....\r\n");
    }
    /* ����Ƿ��ⲿ��λ */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n �����ⲿ��λ....\r\n");
    }

    printf("\r\n ����Ҫ��������RTC....\r\n");
    
    /* ʹ�� PWR ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /* PWR_CR:DBF��1��ʹ��RTC��RTC���ݼĴ����ͱ���SRAM�ķ��� */
    PWR_BackupAccessCmd(ENABLE);
    /* �ȴ� RTC APB �Ĵ���ͬ�� */
    RTC_WaitForSynchro();

    /* ���RTC�жϱ�־λ */
    RTC_ClearFlag(RTC_FLAG_ALRAF);
    /* ��� EXTI Line 17 ����λ (�ڲ����ӵ�RTC Alarm) */
    EXTI_ClearITPendingBit(EXTI_Line17);		
  } 
	
	/* ��ʾʱ������� */
	RTC_TimeAndDate_Show();
}


/**********************************END OF FILE*************************************/
