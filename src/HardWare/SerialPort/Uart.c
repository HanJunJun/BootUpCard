

#include "Uart.h"



#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1


u8 xdata RX_buffer[tbuf];


//extern u8 RX_buffer[tbuf];

void UartInit(void)
{

	//PCON &= 0x7F;		//����֡���
	SCON = 0x50;		//8λ���ݣ��ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��1ΪFOSC,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1����ģʽ0 Ϊ16λ�Զ���װ��ʽ

	TL1 = (65536 - (11059200 / 4 / 115200));    //���ö�ʱ��ֵ
	TH1 = (65536 - (11059200 / 4 / 115200)) >> 8; //���ö�ʱ��ֵ
	//TL1 = (65536 - (11059200 / 4 / 9600));    //���ö�ʱ��ֵ
	//TH1 = (65536 - (11059200 / 4 / 9600)) >> 8; //���ö�ʱ��ֵ

	//ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1

	S2CON = 0x50;		//8λ���ݣ��ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��1ΪFOSC,��1T

	T2L = (65536 - (11059200 / 4 / 115200));    //���ö�ʱ��ֵ
	T2H = (65536 - (11059200 / 4 / 115200)) >> 8; //���ö�ʱ��ֵ

	AUXR |= 0x10;		//������ʱ��2	   

}

/////////////////////////////////
/////////////////////////////////

//����1���ʹ�������(�ֽ�)
void Uart1SendByte(u8 dat)
{
	SBUF = dat;
	while (TI == 0);
	TI = 0;
}

/*
	����eeprom
*/
u8 SendData(u8 dat)
{
	SBUF = dat;				 //��������
	while (TI == 0);			 //�ж��Ƿ������ ��λTI
	TI = 0;					 //���־λ
	return dat;			 //���ط��͵����� Ϊ������׼��
}

/*
	����1��ӡ������Ϣ��PC��
*/
void PrintLog(u8* str)
{
	while (*str)
	{
		Uart1SendByte(*str);
		str++;
	}
}

//����1�����ַ���
void Uart1SendStr(u8* str)
{
	while (*str)
	{
		Uart1SendByte(*str);
		str++;
	}
}

//����1����ָ�������ַ���
void Uart1Send(u8* str, u8 len)
{
	while (len--)
	{
		Uart1SendByte(*str);
		str++;
	}
}

/////////////////////////////////
/////////////////////////////////

//����2���ʹ�������(�ֽ�)
void Uart2SendByte(u8 ch)
{
	S2BUF = ch;                 //д���ݵ�UART2���ݼĴ���
	while (!(S2CON & S2TI));
	S2CON &= ~S2TI;
}

//����2�����ַ���
void Uart2SendStr(u8* s)
{
	IE2 = 0x00;
	while (*s)                  //����ַ���������־
	{
		Uart2SendByte(*s++);     //���͵�ǰ�ַ�
	}
	IE2 = 0x01;
}



/////////////////////////////////
/////////////////////////////////

u8 RX_num = 0;   //���ռ�������

//����1�ж�
void Uart1() interrupt 4 using 1
{
	ES = 0;		   //�رմ���1�ж�
	if (RI)
	{
		RI = 0;                 //���RIλ
		RX_buffer[RX_num] = SBUF;
		RX_num++;
		if (RX_num > tbuf) RX_num = 0;


	}
	if (TI)
	{
		TI = 0;                 //���TIλ

	}
	ES = 1;	  //��������1�ж�

}


//����2�ж�
void Uart2() interrupt 8 using 1
{

	IE2 = 0x00;		  //�رմ���2�ж�
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;
		RX_buffer[RX_num] = S2BUF;
		RX_num++;
		if (RX_num > tbuf) RX_num = 0;
	}
	if (S2CON & S2TI)
	{
		S2CON &= ~S2TI;
	}
	IE2 = 0x01;		//��������2�ж�

}







