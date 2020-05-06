#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "ff.h"
#include "./mjpegplayer/avifile.h"
#include "./mjpegplayer/vidoplayer.h"
#include "./Bsp/lcd/bsp_lcd.h"
#include "./Bsp/wm8978/bsp_wm8978.h"  

FIL       fileR;
UINT      BytesRD;
uint8_t   Frame_buf[1024*30]={0};

static uint8_t audiobufflag=0;
uint8_t   Sound_buf[4][1024*5]={0};

uint8_t   *pbuffer;

uint32_t  mid;
uint32_t  Strsize;
uint16_t  Strtype;


static uint8_t timeout;
extern WAVEFORMAT*   wavinfo;
extern avih_TypeDef* avihChunk;

void MUSIC_I2S_DMA_TX_Callback(void);
extern void mjpegdraw(uint8_t *mjpegbuffer,uint32_t size);
static void TIM3_Config(uint16_t period,uint16_t prescaler);

void AVI_play(char *filename)
{
	FRESULT  res;
  uint32_t offset;
  uint16_t audiosize;
  uint8_t avires=0;
  uint8_t audiosavebuf;
  pbuffer=Frame_buf;
  res=f_open(&fileR,filename,FA_READ);
  if(res!=FR_OK)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"Cannot open file!(1)");	
    return;    
  }
  LCD_DisplayStringLine(0,(uint8_t *)filename);
  
  res=f_read(&fileR,pbuffer,20480,&BytesRD);	  
  avires=AVI_Parser(pbuffer);//����AVI�ļ���ʽ
  if(avires)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File format error!(2)");
    return;    
  }
  
  avires=Avih_Parser(pbuffer+32);//����avih���ݿ�
  if(avires)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File not supported!(3)");
    return;    
  }
  
  avires=Strl_Parser(pbuffer+88);//����strh���ݿ�
  if(avires)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File format error!(4)");
    return;    
  }
  
  avires=Strf_Parser(pbuffer+164);//����strf���ݿ�
  if(res!=FR_OK)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File format error!(5)");
    return;    
  }
  
  mid=Search_Movi(pbuffer);//Ѱ��movi ID		
  if(mid==0)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File format error!(6)");
    return;    
  }
  
  Strtype=MAKEWORD(pbuffer+mid+6);//������
  Strsize=MAKEDWORD(pbuffer+mid+8);//����С
  if(Strsize%2)Strsize++;//������1
  f_lseek(&fileR,mid+12);//������־ID  
  
  offset=Search_Auds(pbuffer);
  if(offset==0)
  {
    LCD_DisplayStringLine(40,(uint8_t *)"File format error!(6)");
    return;    
  }  
  audiosize=*(uint8_t *)(pbuffer+offset+4)+256*(*(uint8_t *)(pbuffer+offset+5));
  if(audiosize==0)
  {
    offset=(uint32_t)pbuffer+offset+4;
    mid=Search_Auds((uint8_t *)offset);
    if(mid==0)
    {
      LCD_DisplayStringLine(40,(uint8_t *)"File format error!(6)");
      return;    
    }
    audiosize=*(uint8_t *)(mid+offset+4)+256*(*(uint8_t *)(mid+offset+5));
  }
  
  I2S_Stop();			/* ֹͣI2S¼���ͷ��� */
	wm8978_Reset();		/* ��λWM8978����λ״̬ */	
  	/* ����WM8978оƬ������ΪDAC�����Ϊ���� */
	wm8978_CfgAudioPath(DAC_ON, EAR_LEFT_ON | EAR_RIGHT_ON);

	/* ����������������ͬ���� */
	wm8978_SetOUT1Volume(35);

	/* ����WM8978��Ƶ�ӿ�Ϊ�����ֱ�׼I2S�ӿڣ�16bit */
	wm8978_CfgAudioIF(I2S_Standard_Phillips, 16);
  I2S_GPIO_Config();
  I2Sx_Mode_Config(I2S_Standard_Phillips, I2S_DataFormat_16b, wavinfo->SampleRate);
  I2S_DMA_TX_Callback=MUSIC_I2S_DMA_TX_Callback;			//�ص�����ָwav_i2s_dma_callback
	I2S_Play_Stop();
  I2Sx_TX_DMA_Init((uint16_t *)Sound_buf[1],(uint16_t *)Sound_buf[2],audiosize/2);
	audiobufflag=0;	    
  timeout=0;
  audiosavebuf=0;
  audiobufflag=0;
  TIM3_Config((avihChunk->SecPerFrame/100)-1,9000-1);
  I2S_Play_Start();  
  while(1)//����ѭ��
  {					
    if(Strtype==T_vids)//��ʾ֡
    {      
      pbuffer=Frame_buf;
      f_read(&fileR,pbuffer,Strsize+8,&BytesRD);//������֡+��һ������ID��Ϣ
      mjpegdraw(pbuffer,BytesRD);
      while(timeout==0)
      {        
        __WFI();
      }
      timeout=0;
    }//��ʾ֡
    else if(Strtype==T_auds)//��Ƶ���
    { 
      uint8_t i;
      audiosavebuf++;
      if(audiosavebuf>3)audiosavebuf=0;
      do
      {
        i=audiobufflag;
        if(i)i--;
        else i=3; 
      }while(audiobufflag==i);
      f_read(&fileR,Sound_buf[audiosavebuf],Strsize+8,&BytesRD);//������֡+��һ������ID��Ϣ
		  pbuffer=Sound_buf[audiosavebuf];      
    }
    else break;
    Strtype=MAKEWORD(pbuffer+Strsize+2);//������
    Strsize=MAKEDWORD(pbuffer+Strsize+4);//����С									
    if(Strsize%2)Strsize++;//������1							   	
  }
  I2S_Play_Stop();
  I2S_Stop();		/* ֹͣI2S¼���ͷ��� */
	wm8978_Reset();	/* ��λWM8978����λ״̬ */
  TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,DISABLE); //ʹ�ܶ�ʱ��3
  f_close(&fileR);
}

void MUSIC_I2S_DMA_TX_Callback(void)
{
  audiobufflag++;
  if(audiobufflag>3)audiobufflag=0;
	if(DMA1_Stream4->CR&(1<<19)) //��ǰ��ȡMemory1����
	{
		DMA_MemoryTargetConfig(DMA1_Stream4,(uint32_t)Sound_buf[audiobufflag], DMA_Memory_0);
	}
	else
	{
		DMA_MemoryTargetConfig(DMA1_Stream4,(uint32_t)Sound_buf[audiobufflag], DMA_Memory_1); 
	}
}

/**
  * @brief  ͨ�ö�ʱ��3�жϳ�ʼ��
  * @param  period : �Զ���װֵ��
  * @param  prescaler : ʱ��Ԥ��Ƶ��
  * @retval ��
  * @note   ��ʱ�����ʱ����㷽��:Tout=((period+1)*(prescaler+1))/Ft us.
  *          Ft=��ʱ������Ƶ��,ΪSystemCoreClock/2=90,��λ:Mhz
  */
static void TIM3_Config(uint16_t period,uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=prescaler;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=period;   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  ��ʱ��3�жϷ�����
  * @param  ��
  * @retval ��
  */
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{    
    timeout=1;
	}
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ	
}
