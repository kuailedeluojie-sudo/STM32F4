/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   通用定时器级联同步
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./tim/bsp_general_tim.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void) 
{	
  /* 初始化通用定时器级联同步PWM输出 */
	/* 实现：TIM2发生事件更新时发送触发信号驱动TIM3计数 */
	/*       TIM3发生事件更新时发送触发信号驱动TIM4计数 */
	TIMx_Configuration();
  
  while(1)
  {    
  }
}



/*********************************************END OF FILE**********************/

