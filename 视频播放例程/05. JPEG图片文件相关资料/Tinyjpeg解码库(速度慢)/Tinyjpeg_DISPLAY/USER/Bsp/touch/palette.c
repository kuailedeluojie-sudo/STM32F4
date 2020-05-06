/**
  ******************************************************************************
  * @file    palette.c
  * @author  fire
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   ��������Ӧ�ú���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "./touch/palette.h"
#include "./touch/gt9xx.h"
#include "./lcd/bsp_lcd.h"


/*
 * �����ʼ��������ȡɫ��
 */
void Palette_Init(void)
{


  /* ������Ϊ��ɫ */
  LCD_Clear(LCD_COLOR_WHITE);
	
  LCD_SetTextColor(LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,0,50,50);

  LCD_SetTextColor(LCD_COLOR_GREY);
  LCD_DrawFullRect(0,50,50,50);

  LCD_SetTextColor(LCD_COLOR_BLUE);
  LCD_DrawFullRect(0,100,50,50);

  LCD_SetTextColor(LCD_COLOR_BLUE2);
  LCD_DrawFullRect(450,300,50,50);

  LCD_SetTextColor(LCD_COLOR_RED);
  LCD_DrawFullRect(0,200,50,50);

  LCD_SetTextColor(LCD_COLOR_MAGENTA);
  LCD_DrawFullRect(0,250,50,50);

  LCD_SetTextColor(LCD_COLOR_GREEN);
  LCD_DrawFullRect(0,300,50,50);

  LCD_SetTextColor(LCD_COLOR_CYAN);
  LCD_DrawFullRect(0,350,50,50);

  LCD_SetTextColor(LCD_COLOR_YELLOW);
  LCD_DrawFullRect(0,400,50,50);

  LCD_DrawFullCircle(100,100,50);


}
