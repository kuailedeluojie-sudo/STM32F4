/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��дEEPROM
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
#include "./usart/bsp_debug_usart.h"
#include "./i2c/bsP_i2c_ee.h"
#include "./led/bsp_led.h"




uint8_t cal_flag = 0;
uint8_t k;

/*�洢С�������������飬��7��*/
long double double_buffer[7] = {0};
int int_bufffer[7] = {0};

#define DOUBLE_ADDR       10
#define LONGINT_ADDR      70



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
  Debug_USART_Config(); 

	printf("\r\n ����һ��EEPROM ��дС���ͳ�����ʵ�� \r\n");

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();
 	 
	/*��ȡ���ݱ�־λ*/
  I2C_EE_BufferRead(&cal_flag, 0, 1);
  
	 if( cal_flag != 0xAB )	/*����־����0xcd����ʾ֮ǰ����д������*/
    {      
        printf("\r\nû�м�⵽���ݱ�־��FLASHû�д洢���ݣ���������С��д��ʵ��\r\n");
        cal_flag =0xAB;
        
        /*д���־��0��ַ*/
        I2C_EE_BufferWrite(&cal_flag, 0, 1); 
        
        /*����Ҫд�������*/
        for( k=0; k<7; k++ )
        {
           double_buffer[k] = k +0.1;
           int_bufffer[k]=k*500+1 ;
        }

        /*д��С�����ݵ���ַ10*/
        I2C_EE_BufferWrite((void*)double_buffer,DOUBLE_ADDR, sizeof(double_buffer));
        /*д���������ݵ���ַ60*/
        I2C_EE_BufferWrite((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
              
        printf("��оƬд�����ݣ�");
        /*��ӡ������*/
        for( k=0; k<7; k++ )
        {
          printf("С��tx = %LF\r\n",double_buffer[k]);
          printf("����tx = %d\r\n",int_bufffer[k]);
        }
        
        printf("\r\n�븴λ�����壬�Զ�ȡ���ݽ��м���\r\n");      
		
    }    
    else
    {      
      	 printf("\r\n��⵽���ݱ�־\r\n");

				/*��ȡС������*/
        I2C_EE_BufferRead((void*)double_buffer, DOUBLE_ADDR, sizeof(double_buffer));
				
				/*��ȡ��������*/
        I2C_EE_BufferRead((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
	
			
				printf("\r\n��оƬ�������ݣ�\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("С�� rx = %LF \r\n",double_buffer[k]);
					printf("���� rx = %d \r\n",int_bufffer[k]);				
				}
      
    }   
		
  while (1)
  {      
  }  

}




/*********************************************END OF FILE**********************/

