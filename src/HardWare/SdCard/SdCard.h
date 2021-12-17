



#ifndef SD_H
#define SD_H

//�����붨��
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0����
#define INIT_CMD1_ERROR     0x02 //CMD1����
#define WRITE_BLOCK_ERROR   0x03 //д�����
#define READ_BLOCK_ERROR    0x04 //�������
//-------------------------------------------------------------

#define TRY_TIME 10    //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��
sbit SD_CS=P1^2;
void SdCommand(unsigned char command, unsigned long argument, unsigned char CRC);
unsigned char SdResponse();
unsigned char SdInit(void);
unsigned char SdReadBlock(unsigned char *Block, unsigned long address,int len);

unsigned char SD_read_sector(unsigned long Sector_NUM,unsigned char *Tmp_Buffer);
unsigned char SD_read_Byte(unsigned long addr,unsigned char *Tmp_Buffer,unsigned long Bytes);
unsigned char SD_Reset(void);//SD����λ������SPIģʽ��ʹ��CMD0������0��
#endif
