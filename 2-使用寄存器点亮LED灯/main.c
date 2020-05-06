
/*
	ʹ�üĴ����ķ�������LED��
  */
#include "stm32f4xx.h" 


/**
  *   ������
  */
int main(void)
{	
	/*���� GPIOH ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ��*/
	RCC_AHB1ENR |= (1<<7);	
	
	/* LED �˿ڳ�ʼ�� */
	
	/*GPIOH MODER10���*/
	GPIOH_MODER  &= ~( 0x03<< (2*10));	
	/*PH10 MODER10 = 01b ���ģʽ*/
	GPIOH_MODER |= (1<<2*10);
	
	/*GPIOH OTYPER10���*/
	GPIOH_OTYPER &= ~(1<<1*10);
	/*PH10 OTYPER10 = 0b ����ģʽ*/
	GPIOH_OTYPER |= (0<<1*10);
	
	/*GPIOH OSPEEDR10���*/
	GPIOH_OSPEEDR &= ~(0x03<<2*10);
	/*PH10 OSPEEDR10 = 0b ����2MHz*/
	GPIOH_OSPEEDR |= (0<<2*10);
	
	/*GPIOH PUPDR10���*/
	GPIOH_PUPDR &= ~(0x03<<2*10);
	/*PH10 PUPDR10 = 01b ����ģʽ*/
	GPIOH_PUPDR |= (1<<2*10);
	
	/*PH10 BSRR�Ĵ����� BR10��1��ʹ��������͵�ƽ*/
	GPIOH_BSRR |= (1<<16<<10);
	
	/*PH10 BSRR�Ĵ����� BS10��1��ʹ��������ߵ�ƽ*/
	//GPIOH_BSRR |= (1<<10);

	while(1);

}

// ����Ϊ�գ�Ŀ����Ϊ��ƭ��������������
void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/

