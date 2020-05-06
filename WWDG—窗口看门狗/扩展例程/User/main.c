/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڿ��Ź�����
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
#include "./key/bsp_key.h" 
#include "./wwdg/bsp_wwdg.h"
#include "./systick/bsp_SysTick.h"

/*���������*/
uint32_t Task_Delay[NumOfTask]={40};

/*ֹͣι����־������KEY1��ʹ�����־��1��systickֹͣι��*/
uint8_t stop_feed = 0;

static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
	
	/*��ʼ��systick*/
	SysTick_Init();

	/* ����Ƿ�Ϊ���ڿ��Ź���λ */
  if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
  {
		/*ֹͣι���󣬴�����λ�������������ڣ������*/	

    /* ���ڿ��Ź���λ */
    /*  ����� */
    LED_RED;

    /* �����־ */
    RCC_ClearFlag();		
		
		/*��ʱ�����㸴λ�󿴵������*/
		Delay(0XFFFFFF);	
  }
  else
  {
    /*���Ǵ��ڿ��Ź���λ(����Ϊ�ϵ縴λ֮���) */
    /* ���̵� */
    LED_GREEN;
  }	
	
  
  /*��ʼ������*/
  Key_GPIO_Config();	
	
	// WWDG����
	
	/* WWDG ���ú���
	 * tr ���ݼ���ʱ����ֵ�� ȡֵ��ΧΪ��0x7f~0x40��������Χ��ֱ�Ӹ�λ
	 * wr ������ֵ��ȡֵ��ΧΪ��0x7f~0x40
	 * prv��Ԥ��Ƶ��ֵ��ȡֵ������
	 *      @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1(45MHz)/4096)/1  Լ10968Hz 91us
	 *      @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1(45MHz)/4096)/2	 Լ5484Hz	182us
	 *      @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1(45MHz)/4096)/4	 Լ2742Hz	364us
	 *      @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1(45MHz)/4096)/8  Լ1371Hz	728us
	 *      
	 *			����tr = 127(0x7f��tr�����ֵ)  wr = 80��0x50, 0x40Ϊ��Сwr��Сֵ��  prv =  WWDG_Prescaler_8
	 *			~728 * (127-80) = 34.2ms < ˢ�´��� < ~728 * 64 = 46.6ms
	 *			Ҳ����˵����WWDG_Config�������������ã�����֮���34.2msǰι����ϵͳ�Ḵλ����46.6ms��û��ι����ϵͳҲ�Ḵλ��
	 *			��Ҫ��ˢ�´��ڵ�ʱ����ι����ϵͳ�Ų��Ḵλ��	
	*/	
	WWDG_Config(127,80,WWDG_Prescaler_8);	
	/*���������ι��������40ms��ʼ*/
 	Task_Delay[0]=40;

	while(1)                            
	{		
		//-----------------------------------------------------
		// �ⲿ��Ӧ��д��Ҫ��WWDG��صĳ�����γ������е�ʱ��
		// ������ǰ��WWDG_Config��������ֵ���ݼ�������Ӧ�����óɶ��
		//-----------------------------------------------------
		
		/*���°����󣬽�ֹͣι��*/
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			/*���ñ�־λ������ָʾ��Ҫι��*/
			stop_feed = 1;		
			
			/*����ι�����������λ���ڴ��ڿ��Ź���λǰ������봰�ڿ��Ź��жϣ�����λǰ�Ľ�������*/

		}  
		
		/*��ʱι��*/
		if(Task_Delay[0]==0)
		{						
			if(stop_feed != 1)
			{
				// ι���������ι����ϵͳ��Ḵλ����λ������ƣ�
				//����ڴ���ʱ����׼ʱι���Ļ���������̵�
				WWDG_Feed();		
				//ι�������̵�
				LED_GREEN;
			}		
			Task_Delay[0]=40; //��ֵÿ1ms���1������0�ſ������½�������
		}   

	}
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

