

/***************************************************************************************************                          
* File:   uart.h
* Version: 1.0
* Author: ALGAREEN ENGINEERING 
* Description: Contains the baud rate configurations and function prototypes for UART routines
**************************************************************************************************/

#ifndef _UART_H
#define _UART_H

#include <avr/io.h>		/* include <avr/io.h> where all the Input/Output Registers and its Bits are defined for all AVR micro-controllers*/
#include <util/delay.h> /* include <util/delay.h> which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/
#include <stdlib.h>		/*Includes stdlib.h header file which defines different standard library functions.*/
#include <string.h>		/*Includes string.h header file which defines different functions for String Operations.*/
#include <avr/pgmspace.h>

#define MYUBRR		(((F_CPU / (baudRate * 16UL))) - 1)


/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/

void UART_Init(uint32_t baudRate);
void UART_TxChar(unsigned char v_uartData_u8);
unsigned char UART_RxChar(void);
void UART_TxString(char *ptr_Txstring);
uint8_t UART_RxString( char *ptr_Rxstring);
uint8_t UART_RxStringFULL( char *ptr_Rxstring);
void UART_TxStringfromPROGMEM (const char *ptr_Txstring );


/**************************************************************************************************/

#endif


/***************************************************************************************************
                         void UART_Init(uint32_t v_baudRate_u32)
****************************************************************************************************
 * I/P Arguments: uint32_t : Baud rate to be configured.
 * Return value	: none
 * description  : This function is used to initialize the UART at specified baud rate.
                 		
***************************************************************************************************/
void UART_Init(uint32_t baudRate)
{
	//UCSRA = 0x00;		// Clear UART Status Register 
	
	UCSRC = (0<<URSEL); // Reset URSEL to allow to write in UBRRH
	
	// Set UBRR register with the baud rate
	UBRRH = (unsigned char)(MYUBRR >> 8);
	UBRRL = (unsigned char)(MYUBRR);
	
	UCSRB = (1<<RXEN)|(1<<TXEN); 							// Enable receiver and transmitter and NO INTERRUPT
	UCSRC = (1<<URSEL)|(0<<UMSEL);							// Mode: Asynchronous USART
	
	// set frame format
	UCSRC = (1<<URSEL)|(0<<UPM1)|(0<<UPM0);					// Parity Mode: Disabled
	UCSRC = (1<<URSEL)|(0<<USBS);							// Stop Bit Select: 1-bit
	UCSRC = (1<<URSEL)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);	//Character Size: 8-bit
	
}

/***************************************************************************************************
                         void UART_TxChar(unsigned char data)
****************************************************************************************************
 * I/P Arguments: unsigned char--> Ascii value of the character to be transmitted.
 * Return value	: none.
 * description  :This function is used to transmit a char through UART module.
***************************************************************************************************/
void UART_TxChar(unsigned char data)
{
	//while((UCSRA & 0x20)==0x00) //wait for UDRE flag
	
	while(!(UCSRA & (1<<UDRE))) //wait for UDRE flag
	{
		;
	}
	UDR = data; //load data to UDR for transmission					
}

/***************************************************************************************************
                              char UART_RxChar()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value	: char: Ascii value of the character received

 * description :This function is used to receive a char from UART module.
                It waits till a char is received and returns it after reception.
***************************************************************************************************/
 unsigned char UART_RxChar(void)
 {
	 unsigned char data;
	 //while((UCSRA & 0x80)==0x00)	//wait for RXC flag
	 while(!(UCSRA & (1<<RXC)))	//wait for RXC flag
	 {
		 ;
	 }
	 data = UDR;					//retrieve data from UDR
	 return (data);
 }


/***************************************************************************************************
                         void UART_TxString( char *ptr_Txstring)
****************************************************************************************************
 * I/P Arguments: char *:  Address of the transmitted string/buffer  	
 * Return value	: none
 * description  : This function is used to transmit ASCII string through UART till null terminated is detected
***************************************************************************************************/

void UART_TxString( char *ptr_Txstring)
{
	
	uint8_t len = 0;
	for (len=0; ptr_Txstring[len]!=0;len++)
	{
		UART_TxChar(ptr_Txstring[len]);
	};

}

/***************************************************************************************************
 uint8_t UART_RxString( char *ptr_Rxstring )
****************************************************************************************************
 * I/P Arguments: char *:  Address of the string/buffer where the received data needs to be stored
 * Return value	: uint8_t: Number of chars received.

 * description  :
              1. This function is used to receive a ASCII string through UART till the carriage_return,or New_line, or null character is received.
              2. Once the Carriage_return/New_Line/null is received the string will be null terminated.
***************************************************************************************************/

uint8_t UART_RxString( char *ptr_Rxstring)
{
	char data;
	uint8_t len=0 ;

	len=0;
	
	do
	{
		data=UART_RxChar();	//Receive a char
	} while (data != '\r'); // Terminate the do-loop when the CR is received
	
	data=UART_RxChar();		//Receive the next char of CR which is LF
	
	if (data == '\n')
	{
		do
		{
			data=UART_RxChar();		//Receive a char
			ptr_Rxstring[len]=data; //copy the char into string and increment the index
			len++;
		} while ((data !='\n') && (data !='\r'));
		
		ptr_Rxstring[len-1]='\0';  // null='\n'=0 terminate the string
	}
	
	return (len);
}

/***************************************************************************************************
 uint8_t UART_RxStringFULL( char *ptr_Rxstring )
****************************************************************************************************
 * I/P Arguments: char *:  Address of the string/buffer where the received data needs to be stored
 * Return value	: uint8_t: Number of chars received.

 * description  : This function is used to receive a ASCII string through UART till the  null character is received.

***************************************************************************************************/

uint8_t UART_RxStringFULL( char *ptr_Rxstring)
{
	uint8_t len;
	unsigned char data;
	
	for (len=0; ptr_Rxstring[len]!='\0';len++)
	{
		data=UART_RxChar();
		ptr_Rxstring[len]=data;
	};

	if (len>0) 	ptr_Rxstring[len]='\0'; // Terminate the received string with null='\0' character
		
	return (len);
}

/***************************************************************************************************
			 void UART_TxStringfromPROGMEM ( const char *ptr_Txstring)
****************************************************************************************************
 * I/P Arguments: char *:  Address of the transmitted string/buffer  
 * Return value	: none
 * description  : This function is used to transmit/receive a ASCII string through UART till the null terminated is detected.
***************************************************************************************************/
void UART_TxStringfromPROGMEM (const char *ptr_Txstring)
{
	uint8_t i;
	
	for (i=0; pgm_read_byte(ptr_Txstring) !='\0'; i++)
	{
		UART_TxChar(pgm_read_byte(ptr_Txstring++));
	};
}

/***************************************************************************************************
										END OF UART HEADER FILE
***************************************************************************************************/