#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long

#include "si_toolchain.h"
#include "C8051F020_defs.h"
#include "absacc.h"
#include "Init_DeviceA.c"

sbit KEY1	=  	P1^4;																						//����P1.0Ϊ��ӡ��æ����ź���
sbit KEY2  	= 	P1^5;
sbit KEY3  	= 	P1^6;
sbit KEY4  	= 	P1^7;
int zs_point=0,xs_point=0,caozuoshu1=0,caozuoshu2=0;
uchar keystate=-1,buf1;
																											//��������
void init_UART(void);																						//���ô��ڹ�����ʽ�������ʡ�
void send_1byte(uchar dat);																					//����1���ֽ�
uchar receive_1byte();																						//����1���ֽ�
uchar read_key();																							//������ȡ����
int Count(int shiwei,int gewei,int mode);																	//�������㺯����ģʽ0Ϊ0_63��ģʽ1Ϊ0_38��ģʽ2Ϊ0_17
void SendFF(int num);
void Send(int num,int mode);
void Receive(int num);
void delay(void);
void delay1(void); 
uchar table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF};


void main()
{
	uchar a=-1,b=-1,c=-1;
	int caozuoshu1=0,caozuoshu2=0,shiwei=0,gewei=0;

	Init_DeviceA();
	init_UART();																							//���ô��ڹ�����ʽ�������ʡ�

	while(1)
	{
tuichu:
		//ÿ�β����ָ���ʼ״̬
		a=-1,b=-1,c=-1,caozuoshu1=0,caozuoshu2=0,shiwei=0,gewei=0,keystate=-1,zs_point=0,xs_point=0;      	//������ʼ��

		P2=table[14];
		P3=table[0];
		a=read_key();						//read_key�������趨  ���ز���1 2 3 4    ||2024.4.4
		if(a!=-1)
		{
			switch(a)
			{
				case 1:						//����1��ͨ																//ѡ���������0-3
					P2=table[3];
					P3=table[0];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//ѡ���������0
								P3=0x88;
								P2=table[0];//��ʾA0
								while(1)
								{
									c=read_key();
									if(zs_point==1){P3=0x7f;}								//С����λ���𣬱�ʶ����ִ�еĲ���
									if(xs_point==1){P2=0x7f;}
									switch(c)
									{
										case 1:																		//��������������ʮ���ƣ�
											caozuoshu1=Count(shiwei,gewei,0);
											zs_point=1;
											break;
										case 2:																		//����С��
											caozuoshu2=Count(shiwei,gewei,0);
											xs_point=1;
											break;
										case 3:																		//�˳�
											goto tuichu;
											break;
										case 4:																		//ȷ�ϲ�����
											send_1byte('I');
											send_1byte('R');
											send_1byte(0xa0);
											send_1byte(caozuoshu1);
											send_1byte(caozuoshu2);
											goto tuichu;
											break;
									}
								}
								break;
							case 2:																					//ѡ���������1
								SendFF(1);
								goto tuichu;
								break;
							case 3:																					//ѡ���������2
								SendFF(2);
								goto tuichu;
								break;
							case 4:																					//ѡ���������3
								SendFF(3);
								goto tuichu;
								break;
						}
					}
					break;
				case 2:																			//ѡ���������4-7	20244.4.5
					P3=table[4];
					P2=table[7];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//ѡ���������4
								P3=table[10];
								P2=table[4];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//��������
											caozuoshu1=Count(shiwei,gewei,1);
											zs_point=1;
											break;
										case 2:																			//����С��
											caozuoshu2=Count(shiwei,gewei,1);
											xs_point=1;
											break;
										case 3:																			//�˳�
											goto tuichu;
											break;
										case 4:																			//ȷ�ϲ�����
											send_1byte('I');
											send_1byte('R');
											send_1byte(0xa4);
											send_1byte(caozuoshu1);
											send_1byte(caozuoshu2);
											goto tuichu;
											break;
									}
								}
								break;
							case 2:																					//ѡ���������5
								P3=table[10];
								P2=table[5];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//��������
											caozuoshu1=Count(shiwei,gewei,1);
											zs_point=1;
											break;
										case 2:																			//����С��
											caozuoshu2=Count(shiwei,gewei,1);
											xs_point=1;
											break;
										case 3:																			//�˳�
											goto tuichu;
											break;
										case 4:																			//ȷ�ϲ�����
											send_1byte('I');
											send_1byte('R');
											send_1byte(0xa5);
											send_1byte(caozuoshu1);
											send_1byte(caozuoshu2);
											goto tuichu;
											break;
									}
								}
								break;
							case 3:																					//ѡ���������6
								P3=table[10];
								P2=table[6];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//��������
											caozuoshu1=Count(shiwei,gewei,2);
											zs_point=1;
											break;
										case 2:																			//����С��
											caozuoshu2=Count(shiwei,gewei,2);
											xs_point=1;
											break;
										case 3:																			//�˳�
											goto tuichu;
											break;
										case 4:																			//ȷ�ϲ�����
											send_1byte('I');
											send_1byte('R');
											send_1byte(0xa6);
											send_1byte(caozuoshu1);
											send_1byte(caozuoshu2);
											goto tuichu;
											break;
									}
								}
								break;
							case 4:																					//ѡ���������7
								P3=table[10];
								P2=table[7];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//��������
											caozuoshu1=Count(shiwei,gewei,2);
											zs_point=1;
											break;
										case 2:																			//����С��
											caozuoshu2=Count(shiwei,gewei,2);
											xs_point=1;
											break;
										case 3:																			//�˳�
											goto tuichu;
											break;
										case 4:																			//ȷ�ϲ�����
											send_1byte('I');
											send_1byte('R');
											send_1byte(0xa7);
											send_1byte(caozuoshu1);
											send_1byte(caozuoshu2);
											goto tuichu;
											break;
									}
								}
								break;
						}
					}
					break;
				case 3:																						//ѡ���������8-B  ��״̬
					P3=table[8];
					P2=table[11];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//ѡ���������8
								SendFF(8);
								Receive(8);
								goto tuichu;
								break;
							case 2:																					//ѡ���������9
								SendFF(9);
								Receive(9);
								goto tuichu;
								break;
							case 3:																					//ѡ���������A
								SendFF(10);
								Receive(10);
								goto tuichu;
								break;
							case 4:																					//ѡ���������B
								SendFF(11);
								Receive(11);
								goto tuichu;
								break;
						}
					}
					break;
				case 4:																						//ѡ���������C-E
					P3=table[12];
					P2=table[14];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//ѡ���������C
								SendFF(12);
								Receive(12);
								goto tuichu;
								break;
							case 2:																					//ѡ���������D
								SendFF(13);
								Receive(13);
								goto tuichu;
								break;
							case 3:																					//ѡ���������E
								SendFF(14);
								Receive(14);
								goto tuichu;
								break;
						}
					}
					break;
			}
		}
	}
}


uchar read_key()														//������ȡ����������ֵΪ���°������루1��2��3��4��,�ް��������򷵻�-1
{
	if(KEY1==0)
	{
		delay();        												//һ����ʱ
		while(KEY1==0);
		delay();
		KEY1 = 1;
		return 1;
	}
	if(KEY2==0)
	{
		delay();
		while(KEY2==0);
		delay();
		KEY2 = 1;
		return 2;
	}
	if(KEY3==0)
	{
		delay();
		while(KEY3==0);
		delay();
		KEY3 = 1;
		return 3;
	}
	if(KEY4==0)
	{
		delay();
		while(KEY4==0);
		delay();
		KEY4 = 1;
		return 4;
	}
	return -1;
}	


void init_UART(void)																						//���ô��ڹ�����ʽ�������ʡ�
{
	ES0=0;																									//��ֹUART0�ж�
	EIE2=0x00;																								//��ֹUART1�ж�
	CKCON   = 0x00; 																						//ѡ��ϵͳʱ��Ϊʱ��Դ
	T2CON   = 0x00;			//C/T2ʹ��
	SCON0   = 0x50;			//UART0��ʽ1��8λ�ɱ䲨���ʣ���������Ч
	TMOD    = 0x21;			//C/T0��ʽ1,16λ����
	TL1 	= 0xe8;			//C/T1������9600����ֵ
  	TH1 	= 0xe8;			//C/T1������9600����ֵ
	TR1=1;					
}


void send_1byte(uchar dat)//����1���ֽ�
{
	REN0=0;			//UART0��ֹ���գ�������ң�ص����ݷ��ͱ������
	SBUF0=dat;
	while(TI0==0);		//�ȴ�UART0���ͽ�����UART0�����жϱ�־TI0=1��
	TI0=0;	
	REN0=1;			//UART0������գ�REN0=1��
}


uchar receive_1byte()//����1���ֽ�
{
	ulong  i_cont;
	uchar dat;
	
	REN0=1;			//UART0������գ�REN0=1��
	for(i_cont=0;i_cont<20000;i_cont++)
	{
		if(RI0==1)
		{
			RI0=0;
			dat=SBUF0;
			REN0=0;
			return(dat);
		}
	}
	return(0xff);
}


int Count(int shiwei,int gewei,int mode)											//��ֵ���㺯��
{
	int shuzhi=0;
	while(1)
	{
		//if(shiwei==6 && gewei>=3 && mode==0)gewei=3;
		//if(shiwei==3 && gewei>=8 && mode==1)gewei=8;
		//if(shiwei==1 && gewei>=7 && mode==2)gewei=7;
		P3=table[shiwei];
		P2=table[gewei];
		keystate=read_key();					//��������
		if(keystate==1)																//����������ʮλ
		{
			shiwei++;
			//if(shiwei>=6 && mode==0)shiwei=6;
			//if(shiwei>=3 && mode==1)shiwei=3;
			//if(shiwei>=1 && mode==2)shiwei=1;
			keystate=-1;
		}
		if(keystate==2)																//���������ĸ�λ
		{
			gewei++;
			//if(gewei>=9)gewei=9;
			if(gewei>9)					//ʵ�ֽ�λ
			 {
			 	gewei=0;
				shiwei++;
			 }

			keystate=-1;
		}
		if(keystate==3)																//ʮλ��λ������
		{
			shiwei=0;
			gewei=0;
			P3=table[shiwei];
			P2=table[gewei];
			keystate=-1;
		}
		if(keystate==4)																//��ֵ�������
		{
			shuzhi=shiwei*10+gewei;
			shiwei=0;
			gewei=0;
			keystate=-1;
			P2=0xff;
			P3=0xff;
			return shuzhi;
		}
	}
}


void SendFF(int num)  //            ��ǰ��ķ���ָ�ͬ�����͹̶�ָ����ٴ��븴�Ӷ�
{
	int number;
	number=10*16+num;
	P3=0x88;   //��ʾA
	P2=table[num];  //��ʾ����
	send_1byte('I');
	send_1byte('R');
	send_1byte(number);       //���Ͳ�����
	caozuoshu1=255;
	caozuoshu2=255;			 //������ֱ�ӷ���FFH��255��
	send_1byte(caozuoshu1);
	send_1byte(caozuoshu2);
}


void Send(int num,int mode);

void Receive(int num)  //���޸�
{
	int number,record=0;
	uchar buf2,key,a,b;
	while(1)
	{
		buf1=receive_1byte();															//����1���ֽڣ�I
		if(buf1=='I')
		{
			buf1=receive_1byte();														//����1���ֽڣ�R
			if(buf1=='R')
			{
				buf1=receive_1byte();													//����1���ֽڣ�������
				number=10*16+num;
				if(buf1==number)														//��ѯ��ǰ��������
				{
					buf1=receive_1byte();												//����1���ֽ�,����
					buf2=receive_1byte();												//����1���ֽ�,С��
					P3=table[buf1/10]&0x7F;												//Ĭ����ʾ����
					a=buf1%10;
					P2=table[a]&0xFF;     
					while(1)
					{
						key=read_key();
						switch(key)
						{
							case 1:														//����1С����������ʾ�л�
								if(record==0)
								{
									P3=table[buf2/10]&0xFF;
									b=buf2%10;
									P2=table[b]&0x7F;
									record=1;
									break;
								}
								else if(record==1)
								{
									P3=table[buf1/10]&0x7F;
									a=buf1%10;
									P2=table[a]&0xFF;
									record=0;
									break;
								}
							case 2:														//����2�˳���������ҳ��
								record=3;
								break;
						}
						if(record==3)
						{
							break;
						}
					}
				}
			}
		}
		if(record==3)
		{
			break;
		}
	}
}


void delay(void)
{ 
	ulong i;
	for(i=0;i<0x1000;++i);  //0x1000תΪʮ����4096  
}


void delay1(void)
{ 
	ulong i;
	for(i=0;i<0x10000;++i);
}