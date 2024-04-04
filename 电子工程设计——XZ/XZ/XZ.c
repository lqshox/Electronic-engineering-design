#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long

#include "si_toolchain.h"
#include "C8051F020_defs.h"
#include "absacc.h"
#include "Init_DeviceA.c"

sbit KEY1	=  	P1^4;																						//定义P1.0为打印机忙检测信号线
sbit KEY2  	= 	P1^5;
sbit KEY3  	= 	P1^6;
sbit KEY4  	= 	P1^7;
int zs_point=0,xs_point=0,caozuoshu1=0,caozuoshu2=0;
uchar keystate=-1,buf1;
																											//函数声明
void init_UART(void);																						//设置串口工作方式、波特率。
void send_1byte(uchar dat);																					//发送1个字节
uchar receive_1byte();																						//接收1个字节
uchar read_key();																							//按键读取函数
int Count(int shiwei,int gewei,int mode);																	//整数计算函数，模式0为0_63，模式1为0_38，模式2为0_17
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
	init_UART();																							//设置串口工作方式、波特率。

	while(1)
	{
tuichu:
		//每次操作恢复初始状态
		a=-1,b=-1,c=-1,caozuoshu1=0,caozuoshu2=0,shiwei=0,gewei=0,keystate=-1,zs_point=0,xs_point=0;      	//变量初始化

		P2=table[14];
		P3=table[0];
		a=read_key();						//read_key函数的设定  返回参数1 2 3 4    ||2024.4.4
		if(a!=-1)
		{
			switch(a)
			{
				case 1:						//按键1接通																//选择操作命令0-3
					P2=table[3];
					P3=table[0];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//选择操作命令0
								P3=0x88;
								P2=table[0];//显示A0
								while(1)
								{
									c=read_key();
									if(zs_point==1){P3=0x7f;}								//小数点位亮起，标识正在执行的步骤
									if(xs_point==1){P2=0x7f;}
									switch(c)
									{
										case 1:																		//输入整数（返回十进制）
											caozuoshu1=Count(shiwei,gewei,0);
											zs_point=1;
											break;
										case 2:																		//输入小数
											caozuoshu2=Count(shiwei,gewei,0);
											xs_point=1;
											break;
										case 3:																		//退出
											goto tuichu;
											break;
										case 4:																		//确认并发送
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
							case 2:																					//选择操作命令1
								SendFF(1);
								goto tuichu;
								break;
							case 3:																					//选择操作命令2
								SendFF(2);
								goto tuichu;
								break;
							case 4:																					//选择操作命令3
								SendFF(3);
								goto tuichu;
								break;
						}
					}
					break;
				case 2:																			//选择操作命令4-7	20244.4.5
					P3=table[4];
					P2=table[7];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//选择操作命令4
								P3=table[10];
								P2=table[4];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//输入整数
											caozuoshu1=Count(shiwei,gewei,1);
											zs_point=1;
											break;
										case 2:																			//输入小数
											caozuoshu2=Count(shiwei,gewei,1);
											xs_point=1;
											break;
										case 3:																			//退出
											goto tuichu;
											break;
										case 4:																			//确认并发送
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
							case 2:																					//选择操作命令5
								P3=table[10];
								P2=table[5];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//输入整数
											caozuoshu1=Count(shiwei,gewei,1);
											zs_point=1;
											break;
										case 2:																			//输入小数
											caozuoshu2=Count(shiwei,gewei,1);
											xs_point=1;
											break;
										case 3:																			//退出
											goto tuichu;
											break;
										case 4:																			//确认并发送
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
							case 3:																					//选择操作命令6
								P3=table[10];
								P2=table[6];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//输入整数
											caozuoshu1=Count(shiwei,gewei,2);
											zs_point=1;
											break;
										case 2:																			//输入小数
											caozuoshu2=Count(shiwei,gewei,2);
											xs_point=1;
											break;
										case 3:																			//退出
											goto tuichu;
											break;
										case 4:																			//确认并发送
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
							case 4:																					//选择操作命令7
								P3=table[10];
								P2=table[7];
								while(1)
								{
									c=read_key();
									if(zs_point==1){P2=0x7f;}
									if(xs_point==1){P3=0x7f;}
									switch(c)
									{
										case 1:																			//输入整数
											caozuoshu1=Count(shiwei,gewei,2);
											zs_point=1;
											break;
										case 2:																			//输入小数
											caozuoshu2=Count(shiwei,gewei,2);
											xs_point=1;
											break;
										case 3:																			//退出
											goto tuichu;
											break;
										case 4:																			//确认并发送
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
				case 3:																						//选择操作命令8-B  收状态
					P3=table[8];
					P2=table[11];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//选择操作命令8
								SendFF(8);
								Receive(8);
								goto tuichu;
								break;
							case 2:																					//选择操作命令9
								SendFF(9);
								Receive(9);
								goto tuichu;
								break;
							case 3:																					//选择操作命令A
								SendFF(10);
								Receive(10);
								goto tuichu;
								break;
							case 4:																					//选择操作命令B
								SendFF(11);
								Receive(11);
								goto tuichu;
								break;
						}
					}
					break;
				case 4:																						//选择操作命令C-E
					P3=table[12];
					P2=table[14];
					while(1)
					{
						b=read_key();
						switch(b)
						{
							case 1:																					//选择操作命令C
								SendFF(12);
								Receive(12);
								goto tuichu;
								break;
							case 2:																					//选择操作命令D
								SendFF(13);
								Receive(13);
								goto tuichu;
								break;
							case 3:																					//选择操作命令E
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


uchar read_key()														//按键读取函数，返回值为按下按键键码（1、2、3、4）,无按键输入则返回-1
{
	if(KEY1==0)
	{
		delay();        												//一秒延时
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


void init_UART(void)																						//设置串口工作方式、波特率。
{
	ES0=0;																									//禁止UART0中断
	EIE2=0x00;																								//禁止UART1中断
	CKCON   = 0x00; 																						//选择系统时钟为时钟源
	T2CON   = 0x00;			//C/T2使能
	SCON0   = 0x50;			//UART0方式1（8位可变波特率），接收有效
	TMOD    = 0x21;			//C/T0方式1,16位计数
	TL1 	= 0xe8;			//C/T1波特率9600计数值
  	TH1 	= 0xe8;			//C/T1波特率9600计数值
	TR1=1;					
}


void send_1byte(uchar dat)//发送1个字节
{
	REN0=0;			//UART0禁止接收，红外线遥控的数据发送必须如此
	SBUF0=dat;
	while(TI0==0);		//等待UART0发送结束（UART0发送中断标志TI0=1）
	TI0=0;	
	REN0=1;			//UART0允许接收（REN0=1）
}


uchar receive_1byte()//接收1个字节
{
	ulong  i_cont;
	uchar dat;
	
	REN0=1;			//UART0允许接收（REN0=1）
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


int Count(int shiwei,int gewei,int mode)											//数值计算函数
{
	int shuzhi=0;
	while(1)
	{
		//if(shiwei==6 && gewei>=3 && mode==0)gewei=3;
		//if(shiwei==3 && gewei>=8 && mode==1)gewei=8;
		//if(shiwei==1 && gewei>=7 && mode==2)gewei=7;
		P3=table[shiwei];
		P2=table[gewei];
		keystate=read_key();					//按键接收
		if(keystate==1)																//输入整数的十位
		{
			shiwei++;
			//if(shiwei>=6 && mode==0)shiwei=6;
			//if(shiwei>=3 && mode==1)shiwei=3;
			//if(shiwei>=1 && mode==2)shiwei=1;
			keystate=-1;
		}
		if(keystate==2)																//输入整数的个位
		{
			gewei++;
			//if(gewei>=9)gewei=9;
			if(gewei>9)					//实现进位
			 {
			 	gewei=0;
				shiwei++;
			 }

			keystate=-1;
		}
		if(keystate==3)																//十位个位都清零
		{
			shiwei=0;
			gewei=0;
			P3=table[shiwei];
			P2=table[gewei];
			keystate=-1;
		}
		if(keystate==4)																//数值输入完毕
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


void SendFF(int num)  //            与前面的发送指令不同；发送固定指令减少代码复杂度
{
	int number;
	number=10*16+num;
	P3=0x88;   //显示A
	P2=table[num];  //显示数字
	send_1byte('I');
	send_1byte('R');
	send_1byte(number);       //发送操作码
	caozuoshu1=255;
	caozuoshu2=255;			 //操作数直接发送FFH（255）
	send_1byte(caozuoshu1);
	send_1byte(caozuoshu2);
}


void Send(int num,int mode);

void Receive(int num)  //已修改
{
	int number,record=0;
	uchar buf2,key,a,b;
	while(1)
	{
		buf1=receive_1byte();															//接收1个字节，I
		if(buf1=='I')
		{
			buf1=receive_1byte();														//接收1个字节，R
			if(buf1=='R')
			{
				buf1=receive_1byte();													//接收1个字节，操作码
				number=10*16+num;
				if(buf1==number)														//查询当前操作命令
				{
					buf1=receive_1byte();												//接收1个字节,整数
					buf2=receive_1byte();												//接收1个字节,小数
					P3=table[buf1/10]&0x7F;												//默认显示整数
					a=buf1%10;
					P2=table[a]&0xFF;     
					while(1)
					{
						key=read_key();
						switch(key)
						{
							case 1:														//按键1小数、整数显示切换
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
							case 2:														//按键2退出，返回主页面
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
	for(i=0;i<0x1000;++i);  //0x1000转为十进制4096  
}


void delay1(void)
{ 
	ulong i;
	for(i=0;i<0x10000;++i);
}