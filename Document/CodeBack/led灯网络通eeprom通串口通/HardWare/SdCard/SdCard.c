
#include  "stc15f2k60s2.h"

#include "SdCard.h"
#include "../SPI/SPI.h"
#include  "../../Common/Delay.h"







//============================================================
//���SD������Ӧ
unsigned char SdResponse()
{
unsigned char i=0,response;

while(i<=8)
{

response =SPI_SendByte(0xff); //��SD���ж�ȡ����

if(response==0x00) break;	  //�������ֵ��������ֵ ��Ϊ�õ�SD����Ӧ ���Է���
if(response==0x01) break;				 
i++;
}

return response; 
} 



//================================================================
//�����SD��
void SdCommand(unsigned char command, unsigned long argument, unsigned char CRC)
{
						

SD_CS=1;		                                //Ƭѡ����
SPI_SendByte(0xff);
SPI_SendByte(0xff);	 
SPI_SendByte(0xff);							    
SD_CS=0;  										//����SPI����


SPI_SendByte(command|0x40);                     //дһ�ֽڵ�SD
SPI_SendByte(((unsigned char *)&argument)[0]);
SPI_SendByte(((unsigned char *)&argument)[1]);
SPI_SendByte(((unsigned char *)&argument)[2]);
SPI_SendByte(((unsigned char *)&argument)[3]);
SPI_SendByte(CRC);
}




/*********************************************************************
����:SD��д����
����:
����:
����ֵ:
����ֵ:CMD�����,address��ַ,CRC,response���������Ӧֵ
*********************************************************************/

unsigned char Write_Command_SD(unsigned char CMD,unsigned long address,unsigned char CRC,unsigned char response) 
{  
    unsigned char tmp; 
    unsigned char Timeout=0; 

    /* ��߼�����,�����൱��Ҫ */
SD_CS=1;		                                //Ƭѡ����
SPI_SendByte(0xff);
SPI_SendByte(0xff);	 
SPI_SendByte(0xff);							    
SD_CS=0;  										//����SPI���� 


    /* д����� */
    SPI_SendByte(CMD|0x40);

    /* д4�ֽڲ��� */
    SPI_SendByte(address>>24);
    SPI_SendByte(address>>16);
    SPI_SendByte(address>>8);
    SPI_SendByte(address);

    /* дCRC */
    SPI_SendByte(CRC); 

    do
    {

    /* һֱ����ֱ�������Ĳ�����Ӧֵ��ʱ */
    tmp= SPI_SendByte(0xff);
    Timeout++;
    }while((tmp!=response)&&(Timeout<TRY_TIME));

    return(tmp);
}




 /*********************************************************************
����:SD����λ
����:
����:
����ֵ:0��ʾ�ɹ�
����ֵ:
*********************************************************************/

unsigned char SD_Reset(void)//SD����λ������SPIģʽ��ʹ��CMD0������0��
{
    unsigned char i,temp,time;

    SD_CS=0; 
    for(i=0;i<0x0f;i++)//��λʱ������Ҫ��������74��ʱ���źţ����Ǳ���ģ�����
    	SPI_SendByte(0xff);//120��ʱ��

    SD_CS=1;//����Ƭѡ

    time = 0;
    do
     { 
      temp=Write_Command_SD(0x00,0x00,0x95,0x01);//д������0,��ӦֵΪ0x01
	  delay1ms(10);
      time++;
     }while( (temp!=0x01) && (time < TRY_TIME) );//CMD0����ӦΪ0x01


    if(time >= TRY_TIME) 
    { 
    SD_CS=0; //ʹ��Ƭѡ
    SPI_SendByte(0xff);
    return(INIT_CMD0_ERROR);//CMD0д��ʧ��
    }
         

    SD_CS=0;  //ʹ��Ƭѡ
    SPI_SendByte(0xff); //����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 


    /* ���ÿ鳤��512 */
    Write_Command_SD(16,512,0xff,0x00);

    
    return 0;//����0,˵����λ�����ɹ�
}







//��ʼ��SD��
unsigned char SdInit(void)
{
int delay=0, trials=0;
unsigned char i;
unsigned char response=0x01;
	   
SD_CS=1;
	
for(i=0;i<=9;i++)	
SPI_SendByte(0xff);	
 
SD_CS=0;
	
//Send Command 0 to put MMC in SPI mode
SdCommand(0x00,0,0x95);	  

response=SdResponse();	 

if(response!=0x01)			     //�ж��Ƿ���Ӧ�� ���û�� ��ʼ��ʧ��
{
return 0;	 
} 

while(response==0x01)	
{
SD_CS=1;	
SPI_SendByte(0xff);

SD_CS=0;
SdCommand(0x01,0x00ffc000,0xff);
response=SdResponse();
} 
SD_CS=1;
	
SPI_SendByte(0xff);
return 1; 
}





//================================================================
//��SD��ָ����ַд����,һ�����512�ֽ�
/*unsigned char SdWriteBlock(unsigned char *Block, unsigned long address,int len)
{
unsigned int count;
unsigned char dataResp;
//Block size is 512 bytes exactly
//First Lower SS

SD_CS=0;
//Then send write command
SdCommand(0x18,address,0xff);

if(SdResponse()==00)
{
SdWrite(0xff);
SdWrite(0xff);
SdWrite(0xff);
//command was a success - now send data
//start with DATA TOKEN = 0xFE
SdWrite(0xfe);
//now send data
for(count=0;count<len;count++) SdWrite(*Block++);

for(;count<512;count++) SdWrite(0);
//data block sent - now send checksum
SdWrite(0xff); //���ֽ�CRCУ��, Ϊ0XFFFF ��ʾ������CRC
SdWrite(0xff);
dataResp=SdRead();

while(SdRead()==0);

dataResp=dataResp&0x0f; //mask the high byte of the DATA RESPONSE token
SD_CS=1;
SdWrite(0xff);
if(dataResp==0x0b)
{
return 0;
}
if(dataResp==0x05)
return 1;

return 0;
}
return 0;
}  */

//=======================================================================
//��SD��ָ����ַ��ȡ����,һ�����512�ֽ�
/*
unsigned char SdReadBlock(unsigned char *Block, unsigned long address,int len)
{
unsigned int count;
//Block size is 512 bytes exactly
//First Lower SS

 //printf("MMC_read_block\n");

SD_CS=0;
//Then send write command
SdCommand(0x11,address,0xff);

if(SdResponse()==00)
{
//command was a success - now send data
//start with DATA TOKEN = 0xFE
//while(SdRead()!=0xfe);  SPI_SendByte(0xff);
while(SPI_SendByte(0xff)!=0xfe);
for(count=0;count<len;count++) *Block++=SPI_SendByte(0xff);//SdRead(); 
                                    

for(;count<512;count++) SPI_SendByte(0xff);//SdRead();

//data block sent - now send checksum
SPI_SendByte(0xff);
SPI_SendByte(0xff);

//Now read in the DATA RESPONSE token
SD_CS=1;
SPI_SendByte(0xff);

return 1;
}
 //printf("Command 0x11 (Read) was not received by the MMC.\n");
return 0;
}	   
*/


/*********************************************************************
����:SD��������
����:
����:
����ֵ:0��ʾ�ɹ�
����ֵ:Sector_NUMҪ����������, *Tmp_Buffer������ŵĵ�ַ
*********************************************************************/


   
unsigned char SD_read_sector(unsigned long Sector_NUM,unsigned char *Tmp_Buffer) 
{ 
    unsigned int i;
    unsigned char temp=0,retry;

    
	SD_CS=1; 

    retry = 0;
    do
    {
    /* д��CMD17 */

    temp=Write_Command_SD(17,Sector_NUM<<9,0xff,0x00);
    retry++;
    }while((temp!=0x00) && (retry < TRY_TIME)); 


    if (retry >= TRY_TIME) 
    {
    SD_CS=0;
    return READ_BLOCK_ERROR; 
    }


    /* ����0xfe��ͷ  */
    while(SPI_SendByte(0xff)!=0xfe);

     for(i=0;i<512;i++) 
    {
    /* ��������һ�������� */
    Tmp_Buffer[i]=SPI_SendByte(0xff);  
    }

    /* ��2��CRCУ���ֽ� */
    SPI_SendByte(0xff); 
    SPI_SendByte(0xff);  

    SD_CS=0;
    
    /* ��һ���ֽ� */
    SPI_SendByte(0xff); 
    return 0; 
} 
					

/*********************************************************************
����:SD�����ֽ�
����:
����:
����ֵ:
����ֵ:addrΪ��ַ��*Tmp_BufferΪ������������ŵ�ַ��BytesΪҪ���ĸ���
*********************************************************************/
unsigned char SD_read_Byte(unsigned long addr,unsigned char *Tmp_Buffer,unsigned long Bytes) 
{ 
    unsigned int i;
    unsigned char temp=0,retry;

    /* ����16���ÿ鳤�� */
    Write_Command_SD(16,Bytes,0xff,0x00);

    SD_CS=1; 

    retry = 0;

    do
    {
    /* д��CMD17 */
    temp=Write_Command_SD(17,addr,0xff,0x00);
    retry++;
    }
	
	while((temp!=0x00) && (retry < TRY_TIME)); 

	
    if (retry >= TRY_TIME) 
    {
    SD_CS=0; 
    return READ_BLOCK_ERROR; 
    }

    /* ����0xfe��ͷ  */
    while(SPI_SendByte(0xff)!=0xfe);

     for(i=0;i<Bytes;i++) 
    {

        /* ��������һ�������� */
        Tmp_Buffer[i] = SPI_SendByte(0xff);  

    }

    /* ��2��CRCУ���ֽ� */
    SPI_SendByte(0xff); 
    SPI_SendByte(0xff);  

    SD_CS=0; 
    
    /* ��һ���ֽ� */
   SPI_SendByte(0xff); 

    /* ����16�ָ��鳤�� */
    Write_Command_SD(16,512,0xff,0x00);

    
    return 0; 

} 


