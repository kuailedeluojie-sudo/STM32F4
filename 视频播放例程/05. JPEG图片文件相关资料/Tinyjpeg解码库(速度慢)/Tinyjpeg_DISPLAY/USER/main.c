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
extern void jpgDisplay(char *pic_name);
static  void maindelay(uint32_t time)
{
  for(;time!=0;time--)
  {
    __NOP(); __NOP();
    __NOP(); __NOP();
  }
}
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

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOG,GPIO_Pin_9);  //�ر�BL_8782wifiʹ��
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
  LCD_Clear(LCD_COLOR_CYAN);

	while(1)
	{
    jpgDisplay("0:/musicplayer.jpg");
    maindelay(18000000);
    LCD_Clear(LCD_COLOR_CYAN);
    maindelay(18000000);
    jpgDisplay("0:/LuFu.jpg");	 
    maindelay(18000000);
    LCD_Clear(LCD_COLOR_CYAN);
    maindelay(18000000);
    jpgDisplay("0:/456.jpg");	 
    maindelay(18000000);
    LCD_Clear(LCD_COLOR_CYAN);
    maindelay(18000000);
    jpgDisplay("0:/LuFuu.jpg");	 
    maindelay(18000000);
    LCD_Clear(LCD_COLOR_CYAN);
    maindelay(18000000);
    jpgDisplay("0:/123.jpg");	 
    maindelay(18000000);
    LCD_Clear(LCD_COLOR_CYAN);
    maindelay(18000000);
	}

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
