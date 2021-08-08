/*
* admin.c
*
* Created: 7/15/2021 1:05:37 AM
*  Author: Marco
*/

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "admin.h"

volatile static uint8_t au8_PANNumbers[MAX_ACCOUNT_NO][PAN_BYTES_GUARD_NO];
volatile static uint8_t au8_PANNumber[PAN_BYTES_GUARD_NO], au8_AccountBalance[MAX_ACCOUNT_BYTES_NO];
volatile static uint8_t au8_PANAddress, au8_SPACEAddress, au8_AccountBalanceAddress;
volatile static uint8_t pin[PASS_BYTES_GUARD_NO];
volatile static uint8_t user_pin[USER_PASS_BYTES_NO];
volatile static uint8_t gau8_PIN[PASS_BYTES_GUARD_NO] = "1234";
/******************************************************************************
*                         LOCAL FUNCTION IMPLEMENTATION								*
*******************************************************************************/
void reverse(ptr_uint8_t str, uint8_t len)
{
	uint8_t u8_iterator = 0, j = len - 1, temp;
	while (u8_iterator < j) {
		temp = str[u8_iterator];
		str[u8_iterator] = str[j];
		str[j] = temp;
		u8_iterator++;
		j--;
	}
}

uint8_t strToInt (uint8_t str[])
{
	uint8_t n = 0;
	for (uint8_t c = 0; str[c] != '\0'; c++) {
		n = n * 10 + str[c] - '0';
	}
	return n;
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
uint8_t intToStr(uint32_t x, uint8_t str[], uint32_t d)
{
	uint32_t u8_iterator = 0;
	while (x) {
		str[u8_iterator++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (u8_iterator < d)
	str[u8_iterator++] = '0';
	
	reverse(str, u8_iterator);
	str[u8_iterator] = END_OF_STRING;
	return u8_iterator;
}

// Converts a floating-point/double number to a string.
void ftos(float32_t n, ptr_uint8_t res, uint8_t afterpoint)
{
	// Extract integer part
	uint32_t ipart = (uint32_t) n;
	
	// Extract floating part
	float32_t fpart = n - (float32_t)ipart;
	
	// convert integer part to string
	uint32_t u32_iterator = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[u32_iterator] = '.'; // add dot
		
		// Get the value of fraction part up to given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((uint32_t)fpart, res + u32_iterator + 1, afterpoint);
	}
}

uint32_t findLength(ptr_uint8_t str){
	uint32_t size = 0;
	while (str[size])
	{
		size ++;
	}
	
	return size;
}

float32_t stof(ptr_uint8_t str)
{
	
	float32_t result= 0.0;
	uint32_t len = findLength(str);
	uint32_t dotPosition = 0;

	for (uint8_t u8_iterator = 0; u8_iterator < len; u8_iterator++)
	{
		if (str[u8_iterator] == '.')
		{
			dotPosition = len - u8_iterator  - 1;
		}
		else
		{
			result = result * 10.0 + (str[u8_iterator]-'0');
		}
	}

	while (dotPosition--)
	{
		result /= 10.0;
	}

	return result;
	
}

void Init_Drivers()
{
	//UART_Init();
	EEPROM_Init(EEPROM_CH);
}

void Set_PinData()
{
	if (PASS_BYTES_GUARD_NO > MAX_PASS_BYTES_NO)
	{
		return;
	}
	EEPROM_WriteBytes(EEPROM_CH, PASS_BLOCK, PASS_ADDR, (uint8_t*)gau8_PIN, PASS_BYTES_GUARD_NO);
}

void Get_PinData(uint8_t *data)
{
	if (PASS_BYTES_GUARD_NO > MAX_PASS_BYTES_NO)
	{
		return;
	}
	EEPROM_ReadBytes(EEPROM_CH, PASS_BLOCK, PASS_ADDR, data, PASS_BYTES_GUARD_NO);
}

uint8_t Check_WrittenAddresses()
{
	uint8_t count;
	EEPROM_Read(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, &count);
	if(count == 0xFF)
	{
		return FALSE;
	}
	return TRUE;
	
}

void Display_AccountsAvaliable(void)
{
	UART_uint8_tSendString( STRING_ACCOUNTS_AVALIABLE);
	UART_vdSendByte( BACKSPACE);
	UART_uint8_tSendString( au8_PANNumber);
	UART_uint8_tSendString( STRING_WELCOME_END);
}

void Reset_WrittenAddresses()
{
	EEPROM_Write(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, AVALIABLE_ACCOUNTS_NULL);
}

void Set_WrittenAddresses(uint8_t count)
{
	EEPROM_Write(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, count);
	intToStr(count, au8_PANNumber, 0);
	Display_AccountsAvaliable();
}

uint8_t Get_WrittenAddresses(void)
{
	uint8_t count = SPACE_BYTES_NO;
	EEPROM_Read(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, &count);
	
	if (! Check_WrittenAddresses())
	{
		return FALSE;
	}
	intToStr(count, au8_PANNumber, 0);
	
	return count;
}

uint8_t Check_PANExists(uint8_t count)
{
	uint8_t u8_PANExists = FALSE;
	for (uint8_t u8_iterator = 0; u8_iterator < count; u8_iterator++)
	{
		au8_PANAddress = (u8_iterator * TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK,au8_PANAddress, au8_PANNumbers[u8_iterator], PAN_BYTES_GUARD_NO);
		if ((StringCompare(au8_PANNumber, au8_PANNumbers[u8_iterator])))
		{
			u8_PANExists = TRUE;
			UART_uint8_tSendString(STRING_PAN_EXISTS);
			break;
		}
	}
	return u8_PANExists;
}


/******************************************************************************
*                         APIS IMPLEMENTATION											*
*******************************************************************************/

void ADMIN_Mode(void)
{
	uint8_t u8_choice;
// 	Reset_WrittenAddresses();
	Set_PinData();
	ADMIN_Authenticate();
	while(1)
	{
		u8_choice = ADMIN_Interface();
		if (u8_choice == OPTION_EXIT)
		{
			UART_uint8_tSendString( STRING_EXIT);
			break;
		}
		else if (u8_choice == OPTION_SET_CUSTOMER_DATA) ADMIN_SetAccount();
		else if (u8_choice == OPTION_GET_CUSTOMER_DATA) ADMIN_GetAccount();
		else if (u8_choice == OPTION_SET_MAX_ACCOUNT) ADMIN_SetMaxBalance();
		else if (u8_choice == OPTION_GET_MAX_ACCOUNT) ADMIN_GetMaxBalance();
		else UART_uint8_tSendString( STRING_INVALID_CHOICE);
	}
}
void ADMIN_Authenticate(void)
{
	Get_PinData(pin);
	while (TRUE)
	{
		UART_uint8_tSendString( STRING_ENTER_PIN);
		UART_vdSendByte( BACKSPACE);
		UART_uint8_tGetString( user_pin);
		if ((StringCompare(pin, user_pin))) break;
		UART_uint8_tSendString( STRING_INVALID_PIN);
	}
}

uint8_t ADMIN_Interface()
{
	uint8_t u8_choice;
	UART_uint8_tSendString( STRING_WELCOME_START);
	UART_uint8_tSendString( STRING_MENU_SET_CUSTOMER_DATA);
	UART_uint8_tSendString( STRING_MENU_GET_CUSTOMER_DATA);
	UART_uint8_tSendString( STRING_MENU_SET_MAX_ACCOUNT);
	UART_uint8_tSendString( STRING_MENU_GET_MAX_ACCOUNT);
	UART_uint8_tSendString( STRING_MENU_EXIT);
	UART_uint8_tSendString( STRING_WELCOME_END);
	UART_uint8_tSendString( STRING_MENU_CHOICE);
	UART_vdSendByte( BACKSPACE);
	u8_choice = UART_uint8_tGetByte( );
	UART_vdSendByte( NEW_LINE);
	while ((u8_choice > OPTION_EXIT) && (u8_choice < OPTION_SET_CUSTOMER_DATA))
	{
		UART_uint8_tSendString( STRING_INVALID_CHOICE);
		UART_uint8_tSendString( STRING_MENU_CHOICE);
		UART_vdSendByte( BACKSPACE);
		u8_choice = UART_uint8_tGetByte( );

		UART_vdSendByte( NEW_LINE);
		if ((u8_choice < OPTION_EXIT) && (u8_choice > OPTION_SET_CUSTOMER_DATA)) break;
	}
	return u8_choice; 
}
void ADMIN_GetAccount(void)
{
	uint8_t i = 0;
	float32_t f;
	uint8_t count = Get_WrittenAddresses();
	if (! Check_WrittenAddresses())
	{
		UART_uint8_tSendString( STRING_MEMORY_EMPTY);
		return;
	}
	while (i < count)
	{
		au8_PANAddress = (i* TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
		au8_SPACEAddress = au8_PANAddress + PAN_BYTES_NO;
		au8_AccountBalanceAddress = au8_SPACEAddress + SPACE_BYTES_NO;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK,au8_PANAddress, au8_PANNumber, PAN_BYTES_NO);
		UART_uint8_tSendString( STRING_PAN);
		UART_vdSendByte( BACKSPACE);
		UART_uint8_tSendString( au8_PANNumber);
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_AccountBalanceAddress, (uint8_t *) &f, MAX_ACCOUNT_BYTES_NO);
		UART_uint8_tSendString( STRING_ACCOUNT);
		UART_vdSendByte( BACKSPACE);
		ftos(f, au8_AccountBalance, FLOATING_POINT);
		UART_uint8_tSendString( au8_AccountBalance);
		i++;
	}
	UART_uint8_tSendString( STRING_WELCOME_END);
}



void ADMIN_SetAccount(void)
{
	float32_t ufloat_AccountBalance;
	uint8_t count = Get_WrittenAddresses();
	uint8_t temp = count;
	if (count == MAX_ACCOUNT_NO)
	{
		UART_uint8_tSendString( STRING_MEMORY_FULL);
		return;
	}
	while (TRUE)
	{
		UART_uint8_tSendString( STRING_ENTER_PAN);
		UART_vdSendByte( BACKSPACE);
		UART_uint8_tGetString( au8_PANNumber);
		if ((findLength(au8_PANNumber) != PAN_BYTES_NO))
		{
			UART_uint8_tSendString( STRING_INVALID_PAN);
			continue;
		}
		else if (Check_PANExists(temp)) continue;
		else break;
	}
	au8_PANAddress = (count * TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
	au8_SPACEAddress = au8_PANAddress + PAN_BYTES_NO;
	au8_AccountBalanceAddress = au8_SPACEAddress + SPACE_BYTES_NO;
	EEPROM_WriteBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_PANAddress, au8_PANNumber, PAN_BYTES_NO);
	EEPROM_Write(EEPROM_CH, ACCOUNTS_BLOCK,au8_SPACEAddress, END_OF_STRING);
	UART_uint8_tSendString( STRING_ENTER_ACCOUNT);
	UART_vdSendByte( BACKSPACE);
	UART_uint8_tGetString( au8_AccountBalance);
	ufloat_AccountBalance = stof(au8_AccountBalance);
	EEPROM_WriteBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_AccountBalanceAddress, (uint8_t *)&ufloat_AccountBalance, MAX_ACCOUNT_BYTES_NO);
	++count;
	Set_WrittenAddresses(count);
}
void ADMIN_SetMaxBalance(void)
{
	float32_t ufloat_MaximumAccount = 0.0;
	UART_uint8_tSendString( STRING_MAX_ACCOUNT);
	UART_vdSendByte( BACKSPACE);
	UART_uint8_tGetString( au8_AccountBalance);
	ufloat_MaximumAccount = stof(au8_AccountBalance);
	if (ufloat_MaximumAccount < MAX_BALANCE_NO)
	{
		EEPROM_WriteBytes(EEPROM_CH, MAX_ACCOUNT_BLOCK,MAX_ACCOUNT_ADDR, (uint8_t *)&ufloat_MaximumAccount, MAX_ACCOUNT_BYTES_NO);
	}
	else
	{
		UART_uint8_tSendString( STRING_INVALID_MAX_ACCOUNT);
	}
	
}

void ADMIN_GetMaxBalance(void)
{
	float32_t f;
	EEPROM_ReadBytes(EEPROM_CH, MAX_ACCOUNT_BLOCK, MAX_ACCOUNT_ADDR, (uint8_t *) &f, MAX_ACCOUNT_BYTES_NO);
	ftos(f, au8_AccountBalance, FLOATING_POINT);
	UART_uint8_tSendString( au8_AccountBalance);
	UART_uint8_tSendString( STRING_WELCOME_END);
}
