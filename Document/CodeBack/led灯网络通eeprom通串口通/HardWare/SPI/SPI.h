
#ifndef  SPI_H
#define  SPI_H

#include  "Definition.h"	    		  //�궨�� ���ú���

#define  SPIF  0x80		        //SPI������ɱ�־
#define  WCOL  0x40				//SPIд��ͻ��־


#define  SSIG 0X80	           	//1Ϊ����	����IO�ڿ���
#define  SPEN 0x40				//SPIʹ��λ
#define  DORD 0x20				//�趨SPI���� ���շ��͵�λ˳��
#define  MSTR 0x10				//����ģʽѡ��λ
#define  CPOL 0x08				//SPIʱ�Ӽ���
#define  CPHA 0x04				// SPIʱ��	��λѡ��

#define  SPDHH 0x00				//�ٶ�����λ
#define  SPDH  0x01
#define  SPDL  0x02
#define  SPDLL 0x03


 void Init_SPI();		     //SPI��ʼ��
uchar SPI_SendByte(unsigned char SPI_SendData);	 //SPIΪȫ˫��ͨѶ
void SPI_Speed(unsigned char speed);
#endif




















