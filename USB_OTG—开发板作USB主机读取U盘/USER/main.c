/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   USB �������� USB MSC HOST
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
#include "./Bsp/key/bsp_key.h"
#include "ff.h"
#include "./APP/usbh_bsp.h"
#include "string.h"
/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
FRESULT result;
FATFS fs;
FIL file;

//�ݹ�ɨ���ļ�ʱʹ�õ�·��
char scan_path[255] = "0:";

UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
BYTE WriteBuffer[] =              /* д������*/
"��ӭʹ��Ұ��STM32 F429������ �����Ǹ������ӣ��½��ļ�ϵͳ�����ļ�\r\n";  


KEY Key1,Key2;

static void read_write_flie(void);
static FRESULT scan_files (char* path) ;
/**
  ******************************************************************************
  *                                ������
  ******************************************************************************
  */
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* ��ʼ��LED */
	LED_GPIO_Config();
	Key1_GPIO_Config();
	Key2_GPIO_Config();
	KeyCreate(&Key1,GetPinStateOfKey1);
	KeyCreate(&Key2,GetPinStateOfKey2);
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	
  printf("\r\n����һ��USB OTG���̣�STM32��USB������ȡU�� \r\n");
	
	/* Init Host Library */
		USBH_Init(&USB_OTG_Core,
			USB_OTG_HS_CORE_ID,
            &USB_Host,
            &USBH_MSC_cb,
            &USR_cb);
  
  printf("\r\n����KEY1������ɨ��U���е��ļ���");
  printf("\r\n����KEY2�����ɽ����ļ���д���ԡ�\r\n");

	while(1)
	{
    //USB�������
		USBH_Process(&USB_OTG_Core, &USB_Host);
		
		Key_RefreshState(&Key1);//ˢ�°���״̬
		Key_RefreshState(&Key2);//ˢ�°���״̬
		if(Key_AccessTimes(&Key1,KEY_ACCESS_READ)!=0)//���������¹�
		{
			LED2_TOGGLE;

      result = f_mount(&fs,"0:",1);	/* Mount a logical drive */
      if(result != FR_OK)
      {
        printf("\r\n�ļ�ϵͳ����ʧ�ܣ�\r\n");
        continue; 
      }
      printf("\r\nɨ�赽��U���ļ���\r\n");
      
      scan_files(scan_path);
      
			Key_AccessTimes(&Key1,KEY_ACCESS_WRITE_CLEAR);

		}
		if(Key_AccessTimes(&Key2,KEY_ACCESS_READ)!=0)//���������¹�
		{
			LED3_TOGGLE;
      
      
      result = f_mount(&fs,"0:",1);	/* Mount a logical drive */
      if(result != FR_OK)
      {
        printf("\r\n�ļ�ϵͳ����ʧ�ܣ�\r\n");
        continue; 
      }
			
      read_write_flie();		/* ��ȡ��Ŀ¼��test.txt������ */
			
      Key_AccessTimes(&Key2,KEY_ACCESS_WRITE_CLEAR);
		}
	}
}




/**
  * @brief  scan_files �ݹ�ɨ��FatFs�ڵ��ļ�
  * @param  path:��ʼɨ��·��
  * @retval result:�ļ�ϵͳ�ķ���ֵ
  */
static FRESULT scan_files (char* path) 
{ 
  FRESULT res; 		//�����ڵݹ���̱��޸ĵı���������ȫ�ֱ���	
  FILINFO fno; 
  DIR dir; 
  int i;            
  char *fn;        // �ļ���	
	
#if _USE_LFN 
  /* ���ļ���֧�� */
  /* ����������Ҫ2���ֽڱ���һ�����֡�*/
  static char lfn[_MAX_LFN*2 + 1]; 	
  fno.lfname = lfn; 
  fno.lfsize = sizeof(lfn); 
#endif 
  //��Ŀ¼
  res = f_opendir(&dir, path); 
  if (res == FR_OK) 
	{ 
    i = strlen(path); 
    for (;;) 
		{ 
      //��ȡĿ¼�µ����ݣ��ٶ����Զ�����һ���ļ�
      res = f_readdir(&dir, &fno); 								
      //Ϊ��ʱ��ʾ������Ŀ��ȡ��ϣ�����
      if (res != FR_OK || fno.fname[0] == 0) break; 	
#if _USE_LFN 
      fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
      fn = fno.fname; 
#endif 
      //���ʾ��ǰĿ¼������			
      if (*fn == '.') continue; 	
      //Ŀ¼���ݹ��ȡ      
      if (fno.fattrib & AM_DIR)         
			{ 			
        //�ϳ�����Ŀ¼��        
        sprintf(&path[i], "/%s", fn); 		
        //�ݹ����         
        res = scan_files(path);	
        path[i] = 0;         
        //��ʧ�ܣ�����ѭ��        
        if (res != FR_OK) 
					break; 
      } 
			else 
			{ 
				printf("%s/%s\r\n", path, fn);								//����ļ���	
        /* ������������ȡ�ض���ʽ���ļ�·�� */        
      }//else
    } //for
  } 
  return res; 
}

/*
*********************************************************************************************************
*	�� �� ��: read_write_flie
*	����˵��: ��ȡ�ļ�test.txtǰ128���ַ�������ӡ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void read_write_flie(void)
{	

/*----------------------- �ļ�ϵͳ���ԣ�д���� -----------------------------*/
	/* ���ļ�������ļ��������򴴽��� */
	printf("\r\n****** ���������ļ�д�����... ******\r\n");	
	result = f_open(&file, "0:FatFs��д�����ļ�.txt",FA_CREATE_ALWAYS | FA_WRITE );
	if ( result == FR_OK )
	{
		printf("����/����FatFs��д�����ļ�.txt�ļ��ɹ������ļ�д�����ݡ�\r\n");
    /* ��ָ���洢������д�뵽�ļ��� */
		result=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum);
    if(result==FR_OK)
    {
      printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\n",fnum);
      printf("�����ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
    }
    else
    {
      printf("�����ļ�д��ʧ�ܣ�(%d)\n",result);
    }    
		/* ���ٶ�д���ر��ļ� */
    f_close(&file);
	}
	else
	{	
		printf("������/�����ļ�ʧ�ܡ�\r\n");
	}
	
/*------------------- �ļ�ϵͳ���ԣ������� ------------------------------------*/
	printf("****** ���������ļ���ȡ����... ******\r\n");
	result = f_open(&file, "0:FatFs��д�����ļ�.txt", FA_OPEN_EXISTING | FA_READ); 	 
	if(result == FR_OK)
	{
		printf("�����ļ��ɹ���\r\n");
		result = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum); 
    if(result==FR_OK)
    {
      printf("���ļ���ȡ�ɹ�,�����ֽ����ݣ�%d\r\n",fnum);
      printf("����ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);	
    }
    else
    {
      printf("�����ļ���ȡʧ�ܣ�(%d)\n",result);
    }		
	}
	else
	{
		printf("�������ļ�ʧ�ܡ�\r\n");
	}
	/* ���ٶ�д���ر��ļ� */
	f_close(&file);	
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
