
/*
	ʹ�üĴ����ķ�������LED��
  */
#include "stm32f4xx_gpio.h" 

void Delay( uint32_t nCount); 

/**
  *   ��������ʹ�÷�װ�õĺ���������LED��
  */
int main(void)
{	
	GPIO_InitTypeDef InitStruct;
	
	/*���� GPIOH ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ��*/
	RCC->AHB1ENR |= (1<<7);

	/* LED �˿ڳ�ʼ�� */
	
	/*��ʼ��PH10����*/
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	InitStruct.GPIO_Pin = GPIO_Pin_10;
	/*��������ģʽΪ���ģʽ*/
	InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	/*�������ŵ��������Ϊ�������*/
	InitStruct.GPIO_OType = GPIO_OType_PP;
	/*��������Ϊ����ģʽ*/
	InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	/*������������Ϊ2MHz */   
	InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	GPIO_Init(GPIOH, &InitStruct);	

	/*ʹ��������͵�ƽ,����LED1*/
	GPIO_ResetBits(GPIOH,GPIO_Pin_10);

	/*��ʱһ��ʱ��*/
	Delay(0xFFFFFF);	
	
	/*ʹ��������ߵ�ƽ���ر�LED1*/
	GPIO_SetBits(GPIOH,GPIO_Pin_10);
	
	/*��ʼ��PH11����*/
	InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOH,&InitStruct);
	
	/*ʹ��������͵�ƽ������LED2*/
	GPIO_ResetBits(GPIOH,GPIO_Pin_11);

	while(1);

}

//�򵥵���ʱ��������cpuִ��������ָ�����ʱ��
//������ʱʱ�����Լ��㣬�Ժ����ǿ�ʹ�ö�ʱ����ȷ��ʱ
void Delay( uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}

// ����Ϊ�գ�Ŀ����Ϊ��ƭ��������������
void SystemInit(void)
{	
}


///**
//  *   ������,ʹ�ýṹ��ָ�룬ֱ�ӿ��ƼĴ����ķ�ʽ�����
//			����Ȥ���Խ��ע��������һ��
//  */
//int main(void)
//{	
//	/*���� GPIOH ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ��*/
//	RCC->AHB1ENR |= (1<<7);

//	/* LED �˿ڳ�ʼ�� */
//	
//	/*GPIOH MODER10���*/
//	GPIOH->MODER  &= ~( 0x03<< (2*10));	
//	/*PH10 MODER10 = 01b ���ģʽ*/
//	GPIOH->MODER |= (1<<2*10);
//	
//	/*GPIOH OTYPER10���*/
//	GPIOH->OTYPER &= ~(1<<1*10);
//	/*PH10 OTYPER10 = 0b ����ģʽ*/
//	GPIOH->OTYPER |= (0<<1*10);
//	
//	/*GPIOH OSPEEDR10���*/
//	GPIOH->OSPEEDR &= ~(0x03<<2*10);
//	/*PH10 OSPEEDR10 = 0b ����2MHz*/
//	GPIOH->OSPEEDR |= (0<<2*10);
//	
//	/*GPIOH PUPDR10���*/
//	GPIOH->PUPDR &= ~(0x03<<2*10);
//	/*PH10 PUPDR10 = 01b ����ģʽ*/
//	GPIOH->PUPDR |= (1<<2*10);
//	
//	/*PH10 BSRR�Ĵ����� BR10��1��ʹ��������͵�ƽ*/
//	GPIOH->BSRRH |= (1<<10);
//	
//	/*PH10 BSRR�Ĵ����� BS10��1��ʹ��������ߵ�ƽ*/
////	GPIOH->BSRRL |= (1<<10); 

//	while(1);

//}




/*********************************************END OF FILE**********************/

