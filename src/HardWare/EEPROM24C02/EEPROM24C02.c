
/*************************�˲���ΪAT2402����������ʹ��I2C��������*************************************/
#include  "stc15f2k60s2.h"
#include  "../../Common/Sleep.h"
#include  "../../Common/I2C.h"
#include  "EEPROM24C02.h"





//24c Ĭ�ϵ�Ӳ����ַ���� 0xa0  �� 1010   Ȼ��A2 A1 A0  ���һλ Ϊ��дλ  1�� 0д
//24c02  256x8 bit    
//24c04  512x8 bit
//���ӵ�ַ ֻ��8λ�� �����Ҳ��256���ֽ�  ��ô24c04 ��Ҫռ��2��256���ֽ� 
//����24c04Ӳ���ϲ��õ��� ��ҳ����  ����24c02����A0 A1 A2 ����24c04ʱ A0��Ϊ��ҳλ
//��A0Ϊ0 ��ʾ��һҳ д���һҳ256�ֽ�
//��A0Ϊ1 ��ʾ�ڶ�ҳ д��ڶ�ҳ256�ֽ�









//��AT24CXXָ����ַ����һ������
//Addr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24C_Rcvone(u8 Addr)
{
	u8 temp = 0;
	Start_I2c();                //��������
	SendByte(0xa0);             //����д����
	I2c_wait_ack();			   //�ȴ�Ӧ��
	SendByte(Addr);             //���͵�ַ
	I2c_wait_ack();			   //�ȴ�Ӧ��

	Start_I2c();                //������������
	SendByte(0xa1);		       //����Ϊ������
	I2c_wait_ack();			   //�ȴ�Ӧ��;

	temp = RcvByte(0);			   //���ֽ�	��Ӧ��


	Stop_I2c();                 //�������� 
	return temp;
}



//��AT24CXXָ����ַд��һ������	 �˺���ֻ���� c02-c16
//Addr:д�����ݵ�Ŀ�ĵ�ַ    
//Data:Ҫд�������
void AT24C_Sendone(u8 Addr, u8 Data)
{
	Start_I2c();               //��������

	SendByte(0xa0);            //����д����
	I2c_wait_ack();			  //�ȴ�Ӧ��
	SendByte(Addr);            //���͵�ַ
	I2c_wait_ack();			  //�ȴ�Ӧ��
	SendByte(Data);			  //�����ֽ�����
	I2c_wait_ack();			  //�ȴ�Ӧ��
	Stop_I2c();                //�������� 
	delay1ms(10);			  //��������������ֽڵ�ʱ�������ʱ����Ҫ ���򽫻ش���
}


//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//Addr  :��ʼд��ĵ�ַ  
//Data  :���������׵�ַ
//Len   :Ҫд�����ݵĳ���2,4
void AT24C_SendLenByte(u8 Addr, u8* Data, u8 Len)
{
	while (Len--)
	{
		AT24C_Sendone(Addr, *Data);
		Addr++;
		Data++;
	}
}



//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//Addr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
void AT24C_RcvLenByte(u8 Addr, u8* temp, u8 Len)
{

	while (Len)
	{
		*temp++ = AT24C_Rcvone(Addr++);
		Len--;
	}

}







