//------------------------------------------------------------------------------//     
 //	        "Init_DeviceA.c"���豸��ʼ�������飬���������е���Init_DeviceA()       // 
 //------------------------------------------------------------------------------//

/*��ֹ���Ź�����,Դ������C8051F020��config2��reset sources���á�������Խ׶���
  Ҫ�ر�watch_doog���ܣ��������ŵ��Թ��̡������������Ժ��������м��뿴��
  ��������������¿��Կ������Ź����Ա���������ϵͳ�ܹ���λ������������*/

void Reset_Sources_Init()
{
	WDTCN=0xDE;
	WDTCN=0xAD;
}


//���濪�����ú�������ɻ�������ѡ��Ͷ˿���Դ�ķ���
void Port_IO_Init()
{
	XBR0=0x07;	//UART0��TX0,RX0 �����˿�����P0.0,P0.1
			//SPI0��SCK, MISO, MOSI���ӵ��˿�����P0.2,P0.3,P0.4
			//SPI0��NSS���ӵ��˿�����P1.0				
			//MSBus��SDA, SCL���ӵ��˿�����P1.1,P1.2
    
	XBR2=0xC2;	//��ֹ������	
			//���濪��ʹ��
			//ʹ�õͶ�EMI

	P1MDOUT=0x06;
		  
	EMI0CF=0x0F;	//ѡ��P2-P3��Ϊ���߶˿ڣ����÷�ʽ����ʹ���ⲿRAM 
	EMI0TC=0xDF;	//���߷��ʵ�ַ����ʱ��3��SYS����
			//���߷��ʶ�/д������8��SYS����
			//���߷��ʵ�ַ����ʱ��3��SYS����
}

//������ʼ������,ʹ��Ƭ�⾧������
void Oscillator_Init()
{
	uint i=0;
	OSCXCN=0x67;			//ʹ��Ƭ�⾧��г������f>6.7MHz
	for (i=0;i<3000;i++);		//�ȴ�1mS��ɲ���
	while ((OSCXCN & 0x80)==0);	//����ⲿ�����Ƿ���Ч
	OSCICN=0x08;			//ѡ���ⲿ������Ϊϵͳʱ�ӣ���ֹ�ڲ�ʱ��
}									
/* 
//SMBus��ʼ������
void SMBus_Init(void)
{
	SMB0CN=0x40;			//SMBUSʹ�ܣ�Ӧ����Ч
	SMB0CR=0xcd;			//ʱ��Ƶ��100Khz(SYCLK=11.0592Mhz)/96
}

//�ο���ѹԴ��ʼ������
void Voltage_Reference_Init()
{
	REF0CN=0x03;
}

//ADC0��ʼ������
void ADC0_Init()
{
	AMX0CF=0x00;
	AMX0SL=0x00;
	ADC0CF=0x28;
	ADC0CN=0x81;
}

//ADC1��ʼ������
void ADC1_Init()
{
	AMX1SL=0x07;
	ADC1CF=0x19;
	ADC1CN=0x80;
}

void DAC_Init()
{
	DAC0CN=0x84;
	DAC1CN=0x84;

}
 */
// �豸��ʼ�����������������е���Init_DeviceA()
void Init_DeviceA()
{
	Reset_Sources_Init();	//��λԴ��ʼ��
	Port_IO_Init();			//�˿ڳ�ʼ��
	Oscillator_Init();		//ʱ��Դ��ʼ��
	/* 
	SMBus_Init();				//SMBus��ʼ��
	Voltage_Reference_Init();
	ADC0_Init();
	ADC1_Init();
	DAC_Init(); */
}