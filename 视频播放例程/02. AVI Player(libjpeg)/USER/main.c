/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.5.1�汾�⽨�Ĺ���ģ��
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
#include "./Bsp/led/bsp_led.h" 
#include "./Bsp/usart/bsp_debug_usart.h"
#include "ff.h"
#include "./Bsp/lcd/bsp_lcd.h"
#include "./Bsp/wm8978/bsp_wm8978.h" 
/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
FATFS fs;													/* Work area (file system object) for logical drives */
FRESULT result; 
/**
  ******************************************************************************
  *                                ������
  ******************************************************************************
  */
extern void AVI_play(char *filename);

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
	/* ��ʼ��LED */
	LED_GPIO_Config();
	
  BL8782_PDN_INIT();
  
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	
  printf("\r\n this is a fatfs test demo \r\n");
/*************************   flash �ļ�ϵͳ   *********************************************/
	//���ⲿFlash�����ļ�ϵͳ
	result = f_mount(&fs,"0:",1);
	printf("\r\n f_mount res_flash=%d \r\n",result);
	
	/*��ʼ��Һ����*/
  LCD_Init();
  LCD_LayerInit();
  LTDC_Cmd(ENABLE);

	LCD_SetLayer(LCD_BACKGROUND_LAYER);//LCD_BACKGROUND_LAYER LCD_FOREGROUND_LAYER
  
	/* ������Ϊ��ɫ */
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_SetBackColor(LCD_COLOR_BLACK);
  LCD_SetTextColor(LCD_COLOR_WHITE); 

	/* ���WM8978оƬ���˺������Զ�����CPU��GPIO */
	if (wm8978_Init()==0)
	{
		LCD_DisplayStringLine(0,(uint8_t *)"Don't Find WM8978!!!");
		while (1);	/* ͣ�� */
	}
	while(1)
	{
    AVI_play("0:/Thank you.avi");
    LCD_Clear(LCD_COLOR_BLACK);
    AVI_play("0:/xiao cheng da shi.avi");
    LCD_Clear(LCD_COLOR_BLACK);    
	}

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
