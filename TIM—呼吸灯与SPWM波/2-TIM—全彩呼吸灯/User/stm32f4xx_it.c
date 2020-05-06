/**
  ******************************************************************************
  * @file    FMC_SDRAM/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "./led/bsp_breath_led.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

	
	/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
extern uint16_t indexWave[];
	
extern __IO uint32_t rgb_color;
	
void  BRE_TIM_IRQHandler (void)
{
	static uint16_t pwm_index = 0;			//����PWM���
	static uint16_t period_cnt = 0;		//���ڼ���������
	static uint16_t amplitude_cnt = 0;	//���ڼ����ֵ�ȼ�

	if (TIM_GetITStatus(BRE_TIM, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{		
			amplitude_cnt++;
				
			//ÿ��PWM���е�ÿ��Ԫ����AMPLITUDE_CLASS���ȼ���
		  //ÿ����һ�������һ�����壬��PWM���е�Ԫ�ض�ʹ��һ��
		  //ʹ��256�Σ�����RGB��ɫ��������ͨ�����
			if(amplitude_cnt > (AMPLITUDE_CLASS-1))		 						
			{		
				period_cnt++;
				
				//ÿ��PWM���е�ÿ��Ԫ��ʹ��period_class��
				if(period_cnt > period_class)
				{				

					pwm_index++;												//��־PWM��ָ����һ��Ԫ��
				
					//��PWM���ѵ����β������ָ���ͷ
					if( pwm_index >=  POINT_NUM)			
					{
						pwm_index=0;								
					}
					
					period_cnt = 0;											//�������ڼ�����־
				}
				
				amplitude_cnt=0;											//���÷�ֵ������־
			}
			else
			{	
					//ÿ��PWM���е�ÿ��Ԫ����AMPLITUDE_CLASS���ȼ���
					//ÿ����һ�������һ�����壬��PWM���е�Ԫ�ض�ʹ��һ��

					//����RGB��ɫ����ֵ�����ø���ͨ���Ƿ������ǰ��PWM��Ԫ�ر�ʾ������
					//��
					if(((rgb_color&0xFF0000)>>16) >= amplitude_cnt)				
						BRE_TIM->BRE_RED_CCRx = indexWave[pwm_index];	//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
					else
						BRE_TIM->BRE_RED_CCRx = 0;		//�ȽϼĴ���ֵΪ0��ͨ������ߵ�ƽ����ͨ��LED����
					
					//��
					if(((rgb_color&0x00FF00)>>8) >= amplitude_cnt)				
						BRE_TIM->BRE_GREEN_CCRx = indexWave[pwm_index];	//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
					else
						BRE_TIM->BRE_GREEN_CCRx = 0;	//�ȽϼĴ���ֵΪ0��ͨ������ߵ�ƽ����ͨ��LED����
					
					//��
					if((rgb_color&0x0000FF) >= amplitude_cnt)				
						BRE_TIM->BRE_BLUE_CCRx = indexWave[pwm_index];	//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
					else
						BRE_TIM->BRE_BLUE_CCRx = 0;		//�ȽϼĴ���ֵΪ0��ͨ������ߵ�ƽ����ͨ��LED����	

			}					
		
		TIM_ClearITPendingBit (BRE_TIM, TIM_IT_Update);	//����Ҫ����жϱ�־λ
	}
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
