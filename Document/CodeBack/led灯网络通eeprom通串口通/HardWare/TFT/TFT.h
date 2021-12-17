#ifndef R61505V_H
#define R61505V_H
#include  "Definition.h"	    		  //�궨�� ���ú���



#define Bus_16                  //16λ����ģʽ,���ʹ��8λģʽ����ע�ʹ���䣬���ʹ��16λģʽ����򿪴˾�
#define  LCD_DataPortH P2       //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P0       //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����
sbit LCD_RS = P3^7;  		    //����/�����л�
sbit LCD_WR = P4^2;		        //д����
sbit LCD_RD =P4^4;		        //������
sbit LCD_CS=P3^6;		        //Ƭѡ	
sbit LCD_REST = P4^1;	        //��λ   



void Lcd_Init(void);   //��ʼ��
void LCD_Writ_Bus(char VH,char VL);		//��������д�뺯��
void Lcd_Write_Com(char VH,char VL);   //��������-8λ����
void Lcd_Write_Data(char VH,char VL); //��������-8λ����
void Lcd_Write_Data16(uint val);
void Lcd_Write_Com_Data(int com,int val); //������������
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);//�������귶Χ

void Address_setxy(uchar x,uint y);

#endif
