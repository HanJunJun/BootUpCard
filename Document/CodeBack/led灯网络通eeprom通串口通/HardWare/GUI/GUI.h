#ifndef GUI_H
#define GUI_H
#include  "Definition.h"	    		  //�궨�� ���ú���



/*GUI����*/
void GUI_Clear(uint color);	//����
void GUI_Point(uchar x, uint y, uint color);//����
void GUI_HLine(uchar x, uint y, uchar length, uint color);//������ 
void GUI_SLine(uchar x, uint y, uint high, uint color);//������
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color);//��ֱ��
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high);//��ʾͼƬ(ͼ��)
void GUI_DisPicture(unsigned int x,unsigned int y,unsigned int width,unsigned int height,unsigned char pic[]); //��ʾͼƬ(ͼ��)
void GUI_sprintf_char(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor); //��ʾӢ�Ļ������ַ�
void GUI_sprintf_hz1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ16x16��������
void GUI_sprintf_hzstr16s(unsigned int x1,unsigned int* y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//��ʾӢ���ַ�����16X16����
																													   //����ĺ����Ǵ��ڵ�Ƭ���������

void GUI_sprintf_hz3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ32x32��������
void GUI_sprintf_hz3232s(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);//��ʾ32x32���ִ�
void GUI_sprintf_ZM3216(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int dcolor,unsigned int bgcolor);//��ʾ16x32��ĸ

void GUI_box(uint sx,uint sy,uint ex,uint ey,uint color);//��ʵ�ľ���
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color);//�����ľ���


void PutGB1616(unsigned int x, unsigned int  y, unsigned char Disp_char[2], unsigned int fColor,unsigned int bColor);  //�ɼ�SD�����ֿ� ��ʾ16X16������

void GUI_sprintf_hzstr16x(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);	//


void GUI_sprintf_char_h(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor);   //��ʾ���򵥸��ַ�
void GUI_sprintf_zmhz16(unsigned int x1,unsigned int y1,unsigned char *str,unsigned int dcolor,unsigned int bgcolor); //��ʾ�����ַ�������

void tks(uchar x,uchar y);
void tkx(uchar x,uchar y);
void tkz(uchar x,uchar y);
void tky(uchar x,uchar y);

/*���峣����ɫ����ɫ��*/
#define Red      0xf800	//��
#define Yellow   0xffe0	//��
#define Green    0x07e0	//��
#define Cyan     0x07ff	//��
#define Blue     0x001f	//��
#define Purple   0xf81f	//��
#define Black    0x0000	//��
#define White    0xffff	//��
#define Gray     0x7bef	//��
#define Blue1    0xa5ff //����
#define Purple1  0x8a9e //����
#define Green1   0x0410 //ī��
#endif
















