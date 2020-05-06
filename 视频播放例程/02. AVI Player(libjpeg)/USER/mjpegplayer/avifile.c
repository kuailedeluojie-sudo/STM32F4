#include "./mjpegplayer/avifile.h"
#include <stdio.h>
#include <string.h>

AVI_TypeDef   AVI_file;
avih_TypeDef* avihChunk;
strh_TypeDef* strhChunk;
BITMAPINFO*   bmpinfo;
WAVEFORMAT*   wavinfo;
uint32_t      temp=0x00;
uint8_t       vids_ID;
uint8_t       auds_ID;

uint8_t AVI_Parser(uint8_t *buffer)
{
	temp=ReadUnit(buffer,0,4,1);//��"RIFF"
	if(temp!=RIFF_ID)return 1;
	AVI_file.RIFFchunksize=ReadUnit(buffer,4,4,1);//RIFF���ݿ鳤��
	temp=ReadUnit(buffer,8,4,1);//��"AVI "
	if(temp!=AVI_ID)return 2;
	temp=ReadUnit(buffer,12,4,1);//��"LIST"
	if(temp!=LIST_ID)return 3;
	AVI_file.LISTchunksize=ReadUnit(buffer,16,4,1);//LIST���ݿ鳤��
	temp=ReadUnit(buffer,20,4,1);//��"hdrl"
	if(temp!=hdrl_ID)return 4;
	temp=ReadUnit(buffer,24,4,1);//��"avih"
	if(temp!=avih_ID)return 5;
	AVI_file.avihsize=ReadUnit(buffer,28,4,1);//avih���ݿ鳤��	
	return 0;				
}

uint8_t Avih_Parser(uint8_t *buffer)
{
	avihChunk=(avih_TypeDef*)buffer;
#ifdef DEBUGINFO
	printf("\r\navih���ݿ���Ϣ:");
	printf("\r\nSecPerFrame:%ld",avihChunk->SecPerFrame);
	printf("\r\nMaxByteSec:%ld",avihChunk->MaxByteSec);
	printf("\r\nChunkBase:%ld",avihChunk->ChunkBase);
	printf("\r\nSpecProp:%ld",avihChunk->SpecProp);
	printf("\r\nTotalFrame:%ld",avihChunk->TotalFrame);
	printf("\r\nInitFrames:%ld",avihChunk->InitFrames);
	printf("\r\nStreams:%ld",avihChunk->Streams);
	printf("\r\nRefBufSize:%ld",avihChunk->RefBufSize);
	printf("\r\nWidth:%ld",avihChunk->Width);
	printf("\r\nHeight:%ld\n",avihChunk->Height);
#endif
	if((avihChunk->Width>800)||(avihChunk->Height>480))return 1;//��Ƶ�ߴ粻֧��
	if(avihChunk->Streams!=2)return 2;//��Ƶ������֧��
	return 0;
}

uint8_t Strl_Parser(uint8_t *buffer)
{
	temp=ReadUnit(buffer,0,4,1);//��"LIST"
	if(temp!=LIST_ID)return 1;
	AVI_file.strlsize=ReadUnit(buffer,4,4,1);//strl���ݿ鳤��
	temp=ReadUnit(buffer,8,4,1);//��"strl"
	if(temp!=strl_ID)return 2;
	temp=ReadUnit(buffer,12,4,1);//��"strh"
	if(temp!=strh_ID)return 3;
	AVI_file.strhsize=ReadUnit(buffer,16,4,1);//strh���ݿ鳤��
	strhChunk=(strh_TypeDef*)(buffer+20);		 //108
#ifdef DEBUGINFO
	printf("\r\nstrh���ݿ���Ϣ:");	
	printf("\r\nStreamType:%s",strhChunk->StreamType);
	printf("\r\nHandler:%s",strhChunk->Handler);//��������MJPEG
	printf("\r\nStreamFlag:%ld",strhChunk->StreamFlag);
	printf("\r\nPriority:%d",strhChunk->Priority);
	printf("\r\nLanguage:%d",strhChunk->Language);
	printf("\r\nInitFrames:%ld",strhChunk->InitFrames);
	printf("\r\nScale:%ld",strhChunk->Scale);
	printf("\r\nRate:%ld",strhChunk->Rate);
	printf("\r\nStart:%ld",strhChunk->Start);
	printf("\r\nLength:%ld",strhChunk->Length);
	printf("\r\nRefBufSize:%ld",strhChunk->RefBufSize);
	printf("\r\nQuality:%ld",strhChunk->Quality);
	printf("\r\nSampleSize:%ld",strhChunk->SampleSize);
	printf("\r\nFrameLeft:%d",strhChunk->Frame.Left);
	printf("\r\nFrameTop:%d",strhChunk->Frame.Top);
	printf("\r\nFrameRight:%d",strhChunk->Frame.Right);
	printf("\r\nFrameBottom:%d\n",strhChunk->Frame.Bottom);
#endif
	if(strhChunk->Handler[0]!='M')return 4;
	return 0;
}

uint8_t Strf_Parser(uint8_t *buffer)
{
	temp=ReadUnit(buffer,0,4,1);//��"strf"
	if(temp!=strf_ID)return 1;
	if(strhChunk->StreamType[0]=='v')//��һ����Ϊ��Ƶ��
	{
		vids_ID='0';
		auds_ID='1';
		bmpinfo=(BITMAPINFO*)(buffer+8);
		wavinfo=(WAVEFORMAT*)(buffer+4332);
	}
	else if(strhChunk->StreamType[0]=='a')//��һ����Ϊ��Ƶ��
	{
		vids_ID='1';
		auds_ID='0';
		wavinfo=(WAVEFORMAT*)(buffer+8);
		bmpinfo=(BITMAPINFO*)(buffer+4332);
	}
#ifdef DEBUGINFO		
	printf("\r\nstrf���ݿ���Ϣ(��Ƶ��):");		
	printf("\r\n���ṹ���С:%ld",bmpinfo->bmiHeader.Size);
	printf("\r\nͼ���:%ld",bmpinfo->bmiHeader.Width);
	printf("\r\nͼ���:%ld",bmpinfo->bmiHeader.Height);
	printf("\r\nƽ����:%d",bmpinfo->bmiHeader.Planes);
	printf("\r\n����λ��:%d",bmpinfo->bmiHeader.BitCount);
	printf("\r\nѹ������:%s",bmpinfo->bmiHeader.Compression);
	printf("\r\nͼ���С:%ld",bmpinfo->bmiHeader.SizeImage);
	printf("\r\nˮƽ�ֱ���:%ld",bmpinfo->bmiHeader.XpixPerMeter);
	printf("\r\n��ֱ�ֱ���:%ld",bmpinfo->bmiHeader.YpixPerMeter);
	printf("\r\nʹ�õ�ɫ����ɫ��:%ld",bmpinfo->bmiHeader.ClrUsed);
	printf("\r\n��Ҫ��ɫ:%ld",bmpinfo->bmiHeader.ClrImportant);

	printf("\r\nstrf���ݿ���Ϣ(��Ƶ��):\n");
	printf("\r\n��ʽ��־:%d",wavinfo->FormatTag);
	printf("\r\n������:%d",wavinfo->Channels);
	printf("\r\n������:%ld",wavinfo->SampleRate);
	printf("\r\n������:%ld",wavinfo->BaudRate);
	printf("\r\n�����:%d",wavinfo->BlockAlign);
	printf("\r\n���ṹ���С:%d\n",wavinfo->Size);
#endif
	return 0;
}

uint16_t Search_Movi(uint8_t* buffer)
{
	uint16_t i;
	for(i=0;i<20480;i++)
	{
	   	if(buffer[i]==0x6d)
			if(buffer[i+1]==0x6f)
				if(buffer[i+2]==0x76)	
					if(buffer[i+3]==0x69)return i;//�ҵ�"movi"	
	}
	return 0;		
}

uint16_t Search_Fram(uint8_t* buffer)
{
	uint16_t i;
	for(i=0;i<20480;i++)
	{
	   	if(buffer[i]=='0')
			if(buffer[i+1]==vids_ID)
				if(buffer[i+2]=='d')	
					if(buffer[i+3]=='c')return i;//�ҵ�"xxdc"	
	}
	return 0;		
}
uint16_t Search_Auds(uint8_t* buffer)
{
	uint16_t i;
	for(i=0;i<20480;i++)
	{
	   	if(buffer[i]=='0')
			if(buffer[i+1]==auds_ID)
				if(buffer[i+2]=='w')	
					if(buffer[i+3]=='b')return i;//�ҵ�"xxdc"	
	}
	return 0;		
}

uint32_t ReadUnit(uint8_t *buffer,uint8_t index,uint8_t Bytes,uint8_t Format)//1:���ģʽ;0:С��ģʽ
{
  	uint8_t off=0;
  	uint32_t unit=0;  
  	for(off=0;off<Bytes;off++)unit|=buffer[off+index]<<(off*8);
  	if(Format)unit=__REV(unit);//���ģʽ
  	return unit;
}


