/*
 * APP.c
 *
 * Created: 06-Aug-21 12:34:11 AM
 *  Author: ayman
 */ 
#include "APP.h"

uint8_t value;
uint8_t data[15];
uint8_t admin_flag,flag;
uint8_t choice;
uint8_t status;
uint8_t trial;
uint32_t temp;
uint8_t key;
uint8_t EEpromdata[130];
uint8_t Pindata[5];
uint8_t recieved;
uint8_t checkpan[11];
uint8_t CusNum;
uint8_t amount[7];

uint8_t entryTick;
volatile static uint8_t au8_PANNumber[PAN_BYTES_GUARD_NO], au8_AccountBalance[MAX_ACCOUNT_BYTES_NO];
volatile static uint8_t au8_PANAddress, au8_SPACEAddress, au8_AccountBalanceAddress;


void System_Init()
{
	UART_vdInit();
	LCD_init();
	SPI_vdInit();
	I2C_Init(I2C_CH_0);
	EEPROM_Init(EEPROM_CH_0);
	ADC_init();
	DC_MotorInit();
	BUTTON_init();
	DIO_setPinDirection(PortB,Pin4,OUTPUT);
}

uint8_t System_Update()
{
	if(UART_IsDataReady())
	{
		UART_uint8_tGetString(data);
		if(StringCompare("ADMIN", data))
		{
			ADMIN_Mode();
			return 0;
		}
		else if(StringCompare("USER", data))
		operatingMode();
		else
		UART_uint8_tSendString("wrong command");
	}
}

void operatingMode()
{
	LCD_clearScreen();
	LCD_displayString("1- Insert Card");
	LCD_displayStringRowColumn(1, 0, "2- Display Temp");
	key=KeyPad_getPressedKey();
	switch(key)
	{
		case '1':
		InsertCard();

		break;
		case '2':
		LCD_clearScreen();
		displayTemp();
		break;
		default:
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Entry!");
		}
	}
}

void displayTemp()
{

	LCD_clearScreen();
	temp = ADC_readChannel(0); /* read channel two where the temp sensor is connect */
	/********/
	temp = (temp*150*5)/(1023*1.5); 		/* calculate the temp from the ADC value*/
	LCD_goToRowColumn(0,0);
	LCD_displayString("Temp= ");
	LCD_voidWriteNumber(temp); /* display the temp on LCD screen */
	LCD_displayString(" ");
	LCD_goToRowColumn(0,9);
	LCD_displayCharacter('C');
	LCD_displayStringRowColumn(1, 0, "PRESS 3 TO EXIT");
	while(KeyPad_getPressedKey()!='3');
	LCD_clearScreen();



}
float32_t max_balance;
void InsertCard()
{
	float32_t max_balance;
	float32_t amountavailable;
	float32_t ammountneeded;
	float32_t amountneeded2=0;
	uint8_t panNeeded[10];
	recieved=3;
	LCD_clearScreen();
	LCD_displayString("Verify card");
	while((BUTTON_checkStatus(ButtonCard))==0);
	
	LCD_clearScreen();
	LCD_displayString("Please enter PIN");
	key=KeyPad_getPressedKey();
	LCD_clearScreen();
	for(uint8_t i=0;i<4;i++)
	{
		LCD_displayString("*");
		Pindata[i]=key;
		if(i<3)
		key=KeyPad_getPressedKey();
	}
	DIO_writePin(PortB,Pin4,LOW);
	recieved=SPI_MasterTransmit('P');
	for(uint32_t i=0;i<500000;i++);
	recieved=SPI_MasterTransmit('P');
	for(uint8_t i=0;i<4;i++)
	{
		DIO_writePin(PortB,Pin4,LOW);
		recieved=SPI_MasterTransmit(Pindata[i]);
		for(uint32_t i=0;i<1000;i++);
	}
	for(uint32_t j=0;j<500000;j++);
	DIO_writePin(PortB,Pin4,LOW);
	recieved=SPI_MasterTransmit(30);
	LCD_clearScreen();
	if(recieved==1)
	{
		
		LCD_displayString("Enter the amount");
		LCD_goToRowColumn(1,0);
		for(uint8_t i=0;i<7;i++)
		{
			key=KeyPad_getPressedKey();
			amount[i]=key;
			LCD_displayCharacter(key);
			if(i!=4)
			{
				amountneeded2=amountneeded2*10+key-'0';
			}
		}
		amountneeded2/=100;
		
		EEPROM_ReadBytes(EEPROM_CH, MAX_ACCOUNT_BLOCK, MAX_ACCOUNT_ADDR, (uint8_t *) &max_balance, MAX_ACCOUNT_BYTES_NO);
		if(amountneeded2>max_balance)
		{
			LCD_clearScreen();
			LCD_displayString("above max value");
			SPI_MasterTransmit('W');
			_delay_ms(3000);
			LCD_clearScreen();
		}
		else
		{
			for(uint8_t i=0;i<9;i++)
			{
				panNeeded[i]=SPI_MasterTransmit(1);
				_delay_ms(10);
			}
			
			amountavailable=serverCheck(panNeeded);
			
			if(amountneeded2>amountavailable)
			{
				LCD_clearScreen();
				LCD_displayString("un Sufficient");
				_delay_ms(3000);
				LCD_clearScreen();
				
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("succeeded");
				DC_MotorStart();
				_delay_ms(3000);
				DC_MotorStop();
				LCD_clearScreen();
				
			}
			


		}

	}
	else if (recieved==0)
	{
		LCD_displayString("wrongPassword");
		_delay_ms(3000);
		LCD_clearScreen();
	}
	else
	{
		LCD_displayString("invalid data");
		_delay_ms(3000);
		LCD_clearScreen();
	}

	
}

float32_t serverCheck(uint8_t * recPan)
{
	uint32_t Balance=0;
	uint8_t i = 0;
	float32_t f;
	uint8_t count = Get_WrittenAddresses();
	if (! Check_WrittenAddresses())
	{
		return 0;
	}
	while (i < count)
	{
		au8_PANAddress = (i* TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
		au8_SPACEAddress = au8_PANAddress + PAN_BYTES_NO;
		au8_AccountBalanceAddress = au8_SPACEAddress + SPACE_BYTES_NO;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK,au8_PANAddress, au8_PANNumber, PAN_BYTES_NO);
		if (StringCompare(au8_PANNumber, recPan)) break;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_AccountBalanceAddress, (uint8_t *) &f, MAX_ACCOUNT_BYTES_NO);
		ftos(f, au8_AccountBalance, FLOATING_POINT);
		i++;
		return f;
	}
	return 0;
}
