

#ifndef I2C_H
#define I2C_H
#include "Definition.h"

void Start_I2c();		  //��������
void Stop_I2c();		  //ֹͣ����
void SendByte(u8 c);	  //�ֽ����ݷ��ͺ���
u8  RcvByte(u8 ack);	  //�ֽ����ݽ��պ���	    

u8 I2c_wait_ack(void);	  //�ȴ�Ӧ���źŵ���


#endif
