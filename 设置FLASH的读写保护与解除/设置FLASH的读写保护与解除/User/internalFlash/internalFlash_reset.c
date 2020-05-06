/**
  ******************************************************************************
  * @file    bsp_internalFlash.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �ָ�ѡ���ֽ�ΪĬ��ֵ����(�������д��PCROP����)
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./internalFlash/internalFlash_reset.h" 





/**
  * @brief  InternalFlash_Reset,�ָ��ڲ�FLASH��Ĭ������
  * @param  None
  * @retval None
  */
int InternalFlash_Reset(void)
{
	
	FLASH_Status status = FLASH_COMPLETE;

	
  /* ʹ�ܷ���ѡ���ֽڼĴ��� */
  FLASH_OB_Unlock();
		    
  /* �����û����� (�û�����ָ������û��ʹ�õĿռ䣬�����Զ���)**/
  /* �������FLASH�ı�־λ */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	FLASH_INFO("\r\n");
	FLASH_INFO("����׼���ָ��������������ĵȴ�...");
	
	//ȷ���Ѷ�������������ΪLEVEL1���Ա�ָ�PCROP�Ĵ���λ
	//PCROP�Ĵ���λ������Ϊ0ʱ�������Ƕ�����������LEVEL1תΪLEVEL0ʱ����Ч��
	//�����޸���Ч
	FLASH_OB_RDPConfig(OB_RDP_Level_1);
	
	status=FLASH_OB_Launch();
	
	status = FLASH_WaitForLastOperation();

	//����ΪLEVEL0���ָ�PCROPλ		
	
	FLASH_INFO("\r\n");
	FLASH_INFO("���ڲ����ڲ�FLASH�����ݣ������ĵȴ�...");
	
	//�ر�PCROPģʽ
	FLASH_OB_PCROPSelectionConfig(OB_PcROP_Disable);
	FLASH_OB_RDPConfig(OB_RDP_Level_0);

	status =FLASH_OB_Launch();
	
	//��������λΪĬ��ֵ
	(*(__IO uint32_t *)(OPTCR_BYTE0_ADDRESS))=0x0FFFAAE9;
	(*(__IO uint16_t *)(OPTCR1_BYTE2_ADDRESS))=0x0FFF;
	status =FLASH_OB_Launch();
	
	
	if (status	 != FLASH_COMPLETE)
	{			
		FLASH_ERROR("�ָ�ѡ���ֽ�Ĭ��ֵʧ�ܣ�������룺status=%X",status);		
		
	}
	else
	{
		FLASH_INFO("�ָ�ѡ���ֽ�Ĭ��ֵ�ɹ���");

	}


	//��ֹ����
	FLASH_OB_Lock();

			
	return status;

}




#define FLASH_WRP_SECTORS   (OB_WRP_Sector_0|OB_WRP_Sector_1) 
__IO uint32_t SectorsWRPStatus = 0xFFF;

/**
  * @brief  WriteProtect_Test,��ͨ��д��������
  * @param  ���б�������������FLASH_WRP_SECTORS����д���������ظ�һ�λ���н�д����
  * @retval None
  */
void WriteProtect_Test(void)
{
	FLASH_Status status = FLASH_COMPLETE;	
  {
    /* ��ȡ������д����״̬ */
    SectorsWRPStatus = FLASH_OB_GetWRP() & FLASH_WRP_SECTORS;
		
    if (SectorsWRPStatus == 0x00)
    {
     /* �����ѱ�д������ִ�нⱣ������*/

      /* ʹ�ܷ���OPTCR�Ĵ��� */
      FLASH_OB_Unlock();

      /* ���ö�Ӧ��nWRPλ�����д���� */
      FLASH_OB_WRPConfig(FLASH_WRP_SECTORS, DISABLE); 
			status=FLASH_OB_Launch();
      /* ��ʼ��ѡ���ֽڽ��б�� */  
      if (status	 != FLASH_COMPLETE)
      {
				FLASH_ERROR("��ѡ���ֽڱ�̳������д����ʧ�ܣ�status = %x",status);
        /* User can add here some code to deal with this error */
        while (1)
        {
        }
      }
      /* ��ֹ����OPTCR�Ĵ��� */
      FLASH_OB_Lock();

    /* ��ȡ������д����״̬ */
      SectorsWRPStatus = FLASH_OB_GetWRP() & FLASH_WRP_SECTORS;
  
      /* ����Ƿ����óɹ� */
      if (SectorsWRPStatus == FLASH_WRP_SECTORS)
      {
        FLASH_INFO("���д�����ɹ���");
      }
      else
      {
          FLASH_ERROR("δ���д������");
      }
    }
    else
    { /* ������δ��д����������д�������� */

      /* ʹ�ܷ���OPTCR�Ĵ��� */
      FLASH_OB_Unlock();

      /*ʹ�� FLASH_WRP_SECTORS ����д���� */
      FLASH_OB_WRPConfig(FLASH_WRP_SECTORS, ENABLE); 

			status=FLASH_OB_Launch();
      /* ��ʼ��ѡ���ֽڽ��б�� */  
      if (status	 != FLASH_COMPLETE)
      {
				FLASH_ERROR("��ѡ���ֽڱ�̳�������д����ʧ�ܣ�status = %x",status);        
        while (1)
        {
        }
      }

      /* ��ֹ����OPTCR�Ĵ��� */
      FLASH_OB_Lock();

    /* ��ȡ������д����״̬ */
      SectorsWRPStatus = FLASH_OB_GetWRP() & FLASH_WRP_SECTORS;

      /* ����Ƿ����óɹ� */
      if (SectorsWRPStatus == 0x00)
      {
        FLASH_INFO("����д�����ɹ���");
      }
      else
      {
        FLASH_ERROR("����д����ʧ�ܣ�");
      }
    }
  }
}

/**
  * @brief  SetPCROP,����PCROPλ�����ڲ��Խ���
	*	@note		ʹ��������Ĵ���ISP������������ܻᵼ��PCROPλ��1��
						�����޷���оƬ���س���FLASH�����������ڰ�PCROPλ��1��
						ģ����޷����س���FLASH�Ļ������Ա����ڽ����ĳ�����ԡ�
						�����˽�PCROPλ�����ã��벻Ҫִ�д˺�������
  * @param  None
  * @retval None
  */
void SetPCROP(void)
{
	
	FLASH_Status status = FLASH_COMPLETE;	
	
	OptionByte_Info();
	
	FLASH_INFO();
	FLASH_INFO("��������PCROP�����������ĵȴ�...");
	
	FLASH_OB_Unlock();

	//����ΪPCROPģʽ
	FLASH_OB_PCROPSelectionConfig(OB_PcROP_Enable);
	//��������0����PCROP����
	FLASH_OB_PCROPConfig(OB_PCROP_Sector_10,ENABLE);
	
	status =FLASH_OB_Launch();
	
	if (status	 != FLASH_COMPLETE)
	{			
		FLASH_INFO("����PCROPʧ�ܣ�");
	}
	else
	{
		FLASH_INFO("����PCROP�ɹ���");
	
	}

	FLASH_OB_Lock();
}

/**
  * @brief  OptionByte_Info,��ӡѡ���ֽڵ�������Ϣ
  * @param  None
  * @retval None
  */
void OptionByte_Info(void)
{
	uint32_t temp_optcr = *(uint32_t *)OPTCR_BYTE0_ADDRESS;
	uint32_t temp_optrc1h = *(uint16_t *)OPTCR1_BYTE2_ADDRESS;
	
	uint16_t temp;
	
	FLASH_INFO("\r\n");
	FLASH_INFO("ѡ���ֽڼĴ���OPTCR�����ݣ�0x%08X",temp_optcr);
	FLASH_INFO("ѡ���ֽڼĴ���OPTCR1��16λ�����ݣ�0x%04X",temp_optrc1h);
	
	
	//����������
	FLASH_INFO("\r\n");
	FLASH_INFO("-------------����������-------------");
	if(FLASH_OB_GetRDP()==RESET)
	{
		FLASH_INFO("STM32�ڲ�FLASH����������ΪLEVEL0");	
	}
	else 
	{
		//FLASH_OB_GetRDP��������ֵΪSETʱ������ΪLEVEL1��LEVEL2��
		//����LEVEL2ʱ����RAM���Զ��������У����������޷����ص�оƬ��
		//��LEVEL2ʱоƬ�޷��ٽ���
		FLASH_INFO("�ڲ�FLASH����������ΪLEVEL1");
	}
	
	FLASH_DEBUG("\r\n");
	FLASH_DEBUG("-------------д���Ļ�����-------------");
	temp = FLASH_OB_GetWRP();
	if(temp == 0x0FFF)
	{
		FLASH_DEBUG("Ĭ��ֵ���޶�д������ʹ��single Bankģʽ");
	}
	else if(temp&(1<<15))
		FLASH_DEBUG("ʹ����PCROP���뱣��ģʽ");
	else if(temp&(1<<14))
		FLASH_DEBUG("ʹ����dual bankģʽ");


	
	FLASH_DEBUG("\r\n");	
	FLASH_DEBUG("-------------�û�ѡ���ֽ�USER------------");
	temp = FLASH_OB_GetUser();
	
	if(temp&0x01)
		FLASH_DEBUG("Ĭ��ֵ������������Ź�");
	else
		FLASH_DEBUG("Ӳ���������Ź�");
	
	if(temp&(0x01<<1))
		FLASH_DEBUG("Ĭ��ֵ������ֹͣģʽʱ��������λ");
	else
		FLASH_DEBUG("����ֹͣģʽʱ������λ");

	if(temp&(0x01<<2))	
		FLASH_DEBUG("Ĭ��ֵ���������ģʽʱ��������λ");
	else
		FLASH_DEBUG("�������ģʽʱ������λ");
	
	FLASH_DEBUG("\r\n");	
	FLASH_DEBUG("-------------��λ����BOR_LEV------------");
	temp = FLASH_OB_GetBOR();
	switch(temp)
	{
		case OB_BOR_LEVEL3:
				FLASH_DEBUG("��λ��ֵ��ѹΪ 2.70 V �� 3.60 V");
				break;
		
		case OB_BOR_LEVEL2:
				FLASH_DEBUG("��λ��ֵ��ѹΪ 2.40 V �� 2.70 V");
				break;
		
		case OB_BOR_LEVEL1:
				FLASH_DEBUG("��λ��ֵ��ѹΪ 2.10 V �� 2.40 V");
				break;
			
		case OB_BOR_OFF:
				FLASH_DEBUG("Ĭ��ֵ����λ��ֵ��ѹΪ 1.80 V �� 2.10 V");
				break;	
	}			
				

}	











