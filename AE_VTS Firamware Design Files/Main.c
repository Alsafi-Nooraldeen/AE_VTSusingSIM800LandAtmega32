/*
* AE_VTSusingSIM800LandATmega16.c
*
* Created: 4/12/2020 7:49:04 AM
*  Author: Omer
*/

//------------------------- CPU and RC Internal Oscillator Frequencies --------------------------------------------
#define F_CPU	1000000UL
#define FOSC	1000000UL

//---------------------------------- Header Files-------------------------------------------------------------------
#include <avr/io.h>		/* where all the Input/Output Registers and its Bits are defined for all AVR micro-controllers*/
#include <util/delay.h> /* which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

//---------------------------------- Library Files -----------------------------------------------------------------
#include "LCD2x16.h"
#include "UART.h"
#include "SIM800L.h"

//----------------------------------- Baud Rate --------------------------------------------------------------------
#define BAUDRATE 2400


//------------------------------------Interrupt initialization--------------------------------------------------------

void ExINTERRUPT_Init()
{
	// Set PORTD2/INT0 pin for input (this clears bit DDD2 in the DDR)
	// to check SIM800L RI/RING pin status where its standby status is HIGH:  ---Hi---|__Low__|---Hi---
	DDRD  &=~(1 << PD2);				// Activate interrupt pin INT0
	PORTD |=(1 << PD2);					// Pull-up resistor activated
	MCUCR  =(1 << ISC01)|(0 << ISC00);	// The falling edge of INT0 generates an interrupt request.
	GICR  |=(1 << INT0);				// Start receiving interrupt signal via INT0 at PORTD2 is activated
	sei();								// Activate General External Interrupt
};

//--------------------------------------- Main Programme -----------------------------------------------------------
int main()
{
	//-------------------------------- VARIABLES DECLARATION --------------------------------------------------------
	
	volatile static char RIresponds[12];
	
	uint8_t i, colon_location;
	
	char LONGITUDE[25]="Longitude:";
	char LATITUDE[25] =", Latitude:" ;
	char DATE[20]=", Date:";
	char TIME[20]=", Time:";
	
	//--------------------------- INITIALIZATIONS --------------------------------------------------------------------
	
	ExINTERRUPT_Init();		// Interrupt initialization function
	LCD_Init();				// LCD initialization function
	UART_Init(BAUDRATE);	// UART initialization function with baud rate
	_delay_ms(500);
	
	//-------------------------------------- Welcome Message -------------------------------------------------------
	//
	//LCD_String("** WELCOME TO **");
	//LCD_Command(0xC0);	// go to second line
	//LCD_String("-*-*-*-*-*-*-*-*");
	//_delay_ms(800);
	//LCD_Clear();
	//LCD_String("** Vehicle Tracking System (VTS)**");
	//LCD_Command(0xC0);	// go to second line
	//LCD_String("by Algareen Engineering (AE),Sudan");
	//_delay_ms(600);
	//// Shift Left the entire LCD three times (3x40=120)
	//for (i=0; i<120; i++)
	//{
	//_delay_ms(50);		// delay in m-second
	//LCD_Command(0x18); //Shift entire display to the Left
	//}
	//_delay_ms(600);
	//LCD_Clear();
	//LCD_String("*WELCOME to VTS*");
	//LCD_Command(0xC0);
	//LCD_String("**by AE, SUDAN**");
	//_delay_ms(200);
	//
	
	/*-----------------------------------------SIM800L Initialization------------------------------------------------------------------
	1. Check AT command.
	2. Set baud rate.
	3. Save the configuration.
	4. Turn off the Echo.
	-------------------------------------------------------------------------------------------------------------------------------------*/
	LCD_Clear();
	LCD_String("GSM MODEM SIM800");
	LCD_Command(0xC0);
	LCD_String("Initialization..");
	_delay_ms(200);
	
	if (CheckAT()>0)
	{
		LCD_Clear();
		LCD_String("GSM MODEM INIT..");
		LCD_Command(0xC0);
		LCD_String("Successful...!!!");
		_delay_ms(1200);
	}
	else
	{
		LCD_Clear();
		LCD_String("RESPONSE ERROR!!");
		LCD_Command(0xC0);
		LCD_String("Check Procedure!");
		_delay_ms(2200);
		
		LCD_Clear();	
		LCD_String("*ERROR HANDLING:");
		LCD_Command(0xC0);
		LCD_String("1-TURN-OF POWER!");
		_delay_ms(2200);
		
		LCD_Clear();
		LCD_String("*ERROR HANDLING:");
		LCD_Command(0xC0);
		LCD_String("2-RESTART GSM !!");
		_delay_ms(2200);
	};
	
	//---------------------------------------Checking the SIM card status  -------------------------------------------------
	
	LCD_Clear();
	LCD_String("SIM CARD STATUS:");
	LCD_Command(0xC0);
	LCD_String("Checking........");
	_delay_ms(200);
	
	if (SIMcardINFO()>0)
	{
		LCD_Clear();
		LCD_String("SIM CARD STATUS:");
		LCD_Command(0xC0);
		LCD_String("Inserted Safely!");
		_delay_ms(1200);
	}
	else
	{ 
		while(SIMcardINFO()<=0)
		{
		LCD_Clear();
		LCD_String("*SIM CARD ERROR:");
		LCD_Command(0xC0);
		LCD_String("Check Procedure!");
		_delay_ms(2200);
		LCD_Clear();
		LCD_String("1-SIM Validity");
		LCD_Command(0xC0);
		LCD_String("2-Re-Insert SIM");
		_delay_ms(2200);
		LCD_Clear();
		LCD_String("3_Restart System");
		//LCD_Command(0xC0);
		//LCD_String("2-SIM Validity");
		_delay_ms(2200);
		}
	};
	
	//--------------------------------------- Checking the Mobile Signal Quality ----------------------------------------------------

	//LCD_Clear();
	//LCD_String("SIGNAL QUALITY..");
	//LCD_Command(0xC0);
	//LCD_String("Checking........");
	//_delay_ms(500);
	//
	//if (CheckSignalQlty()>0)
	//{
		//LCD_Clear();
		//LCD_String("CHCK SGNL QLTY..");
		//LCD_Command(0xC0);
		//LCD_String("InRange:31-98dBm");
		//_delay_ms(1200);
	//}
	//else
	//{
		//LCD_Clear();
		//LCD_String("SGNL QLTY ERROR!");
		//LCD_Command(0xC0);
		//LCD_String("Check Procedure!");
		//_delay_ms(2200);
//
		//LCD_Clear();
		//LCD_String("*ERROR HANDLING:");
		//LCD_Command(0xC0);
		//LCD_String("1-Move Location");
		//_delay_ms(2200);
		//
		//LCD_Clear();
		//LCD_String("*ERROR HANDLING:");
		//LCD_Command(0xC0);
		//LCD_String("2-Check	Antenna");
		//_delay_ms(2200);
	//};
	//
	////--------------------------------------- Checking Phone Registration ----------------------------------------------------
	//
	//LCD_Clear();
	//LCD_String("NW REGISTERATION");
	//LCD_Command(0xC0);
	//LCD_String("Checking........");
	//_delay_ms(500);
	//
	//if (CheckSIM800Lregistration()>0)
	//{
		//LCD_Clear();
		//LCD_String("NW REGISTERATION");
		//LCD_Command(0xC0);
		//LCD_String("Successful...!!!");
		//_delay_ms(1200);
	//}
	//else
	//{
		//LCD_Clear();
		//LCD_String("NW_REGIST ERROR!");
		//LCD_Command(0xC0);
		//LCD_String("Check Procedure!");
		//_delay_ms(2200);
		//
		//LCD_Clear();
		//LCD_String("*ERROR HANDLING:");
		//LCD_Command(0xC0);
		//LCD_String("1-FLYMODE_ON/OFF");
		//_delay_ms(2200);
		//
		//LCD_Clear();
		//LCD_String("*ERROR HANDLING:");
		//LCD_Command(0xC0);
		//LCD_String("2-Check MS .....S");
		//_delay_ms(2200);
		////UART_TxStringfromPROGMEM(FUNFULL);	
	//};
	
	//-------------------------------- IP Based Application Setting (OPEN GPRS) ------------------------------------------
	
	LCD_Clear();
	LCD_String("IP BASED APPS.!!");
	LCD_Command(0xC0);
	LCD_String("GPRS Setting....");
	_delay_ms(500);
	
	if (BEARERconfiguration(1)>0)
	{
		LCD_Clear();
		LCD_String("OPEN THE GPRS.!!");
		LCD_Command(0xC0);
		LCD_String("Successful...!!!");
		_delay_ms(1200);
	}
	else
	{
		LCD_Clear();
		LCD_String("OPEN GPRS ERROR!");
		LCD_Command(0xC0);
		LCD_String("Check Procedure!");
		_delay_ms(1200);
		
		LCD_Clear();
		LCD_String("*ERROR HANDLING:");
		LCD_Command(0xC0);
		LCD_String("Use SMS Services");
		_delay_ms(2200);
	};
	//-------------------------------- IP Based Application Setting (CLOSE GPRS) ------------------------------------------
	
	if (BEARERconfiguration(0)>0)
	{
	LCD_Clear();
	LCD_String("CLOSE THE GPRS.!");
	LCD_Command(0xC0);
	LCD_String("Successful...!!!");
	_delay_ms(1200);
	}
	else
	{
	LCD_Clear();
	LCD_String("CLOSE GPRS ERROR!");
	LCD_Command(0xC0);
	LCD_String("Check Procedure!");
	_delay_ms(1200);
	
	LCD_Clear();
	LCD_String("*ERROR HANDLING:");
	LCD_Command(0xC0);
	LCD_String("Use SMS Services");
	_delay_ms(2200);
	};
	
	//-------------------------------- SETUP HTTP SERVER ------------------------------------------
	
	LCD_Clear();
	LCD_String("SETUP HTTPSERVER");
	LCD_Command(0xC0);
	LCD_String("HTTP Setting....");
	_delay_ms(800);
	
	if ( HTTPsetup()>0)
	{
	LCD_Clear();
	LCD_String("SETUP HTTPSERVER");
	LCD_Command(0xC0);
	LCD_String("Successful...!!!");
	_delay_ms(1200);
	}
	else
	{
	LCD_Clear();
	LCD_String("HTTPSERVER ERROR");
	LCD_Command(0xC0);
	LCD_String("Check Procedure!");
	LCD_Clear();
	LCD_Command(0xC0);
	LCD_String("RESET  SYSTEM");
	_delay_ms(1200);
	};
	
	//-------------------------------- READ GSM LOCATION (latitude and longitude) AND TIME (date and time) ------------------------------------------
	
	LCD_Clear();
	LCD_String("GSM LOC.AND TIME");
	LCD_Command(0xC0);
	LCD_String("Getting.........");
	_delay_ms(500);
	
	if ( GSMLocationTime()>0)
	{
	LCD_Clear();
	LCD_String("GSM LOC.AND TIME");
	LCD_Command(0xC0);
	LCD_String("Successful...!!!");
	_delay_ms(1200);
	
	LCD_Clear();
	LCD_String("Long:");
	LCD_String(longitude);
	LCD_Command(0xC0);
	LCD_String("Lat:");
	LCD_String(latitude);
	
	_delay_ms(1200);
	
	LCD_Clear();
	LCD_String("Date:");
	LCD_String(date);
	LCD_Command(0xC0);
	LCD_String("Time:");
	LCD_String(time);
	
	_delay_ms(1200);
	}
	else
	{
	LCD_Clear();
	LCD_String("GSM LOC.AND TIME");
	LCD_Command(0xC0);
	LCD_String("ERROR Occurred!!");
	_delay_ms(1200);
	};
	
	
	
	//////--------------------------------------- Sending GSM LOCATION and TIME SMS Message ----------------------------------------------------
	////
	////LCD_Clear();
	////LCD_String("SEND GSM LOCATION");
	////LCD_Command(0xC0);
	////LCD_String("SMS Sending...!!");
	////_delay_ms(500);
	////
	//////------------------------------- Concatenates the GSM LOCATION AND TIME ----------------------------------------------------
	////
	////strncat(LONGITUDE, (const char *) longitude, longitude_length);  // concatenates the longitude values with longitude length
	////strncat(LATITUDE, (const char *) latitude, latitude_length);	// concatenates the latitude values with latitude length
	////strncat(DATE, (const char *) date, date_length);				// concatenates the date values with date length
	////strncat(TIME, (const char *) time, time_length);				// concatenates the time values with time length
	////
	////strcat(GSMLOCATIONTIME, (const char *) LONGITUDE);	// concatenates the GSM location with the longitude values
	////strcat(GSMLOCATIONTIME, (const char *) LATITUDE);	// concatenates the GSM location with the longitude and latitude
	////strcat(GSMLOCATIONTIME, (const char *) DATE);		// concatenates the GSM location with the longitude, latitude and date values
	////strcat(GSMLOCATIONTIME, (const char *) TIME);		// concatenates the GSM location with the longitude, latitude, date and time values
	////
	////if (TxSMSviaSIM800L(GSMLOCATIONTIME)>0)
	////{
	////LCD_Clear();
	////LCD_String("SEND SMS MESSAGE");
	////LCD_Command(0xC0);
	////LCD_String("Successful...!!!");
	////_delay_ms(1200);
	////}
	////else
	////{
	////LCD_Clear();
	////LCD_String("SEND SMS MESSAGE");
	////LCD_Command(0xC0);
	////LCD_String("ERROR Occurred!!");
	////_delay_ms(1200);
	////};
	//
	////---------------------------------------------- Receiving SMS Message ----------------------------------------------------
	//
	//LCD_Clear();
	//LCD_String("RECEIVE SMS MSG!");
	//LCD_Command(0xC0);
	//LCD_String("SMS Receiving..!");
	//_delay_ms(500);
	//
	//if (RxSMSviaSIM800L(1)>0)
	//{
	//LCD_Clear();
	//LCD_String("RECEIVE SMS MSG!");
	//LCD_Command(0xC0);
	//LCD_String("Successful...!!!");
	//_delay_ms(1200);
	////--------- SMS MESSAGE DISPLAY ------------------------
	//LCD_Clear();
	//LCD_String("TEL:");
	//LCD_String(RXsmsPHONENO);
	//LCD_Command(0xC0);
	//LCD_String("Name:");
	//LCD_String(RXsmsPHONENAME);
	//_delay_ms(1200);
	//
	//LCD_Clear();
	//LCD_String("Time:");
	//LCD_String(RXsmsDATETIME);
	//LCD_Command(0xC0);
	//LCD_String("SMS:");
	//LCD_String(RXsmsMESSAGE);
	//for (i=0; i<= RXsmsMESSAGE_length; i++)
	//{
	//_delay_ms(50);		// delay in m-second
	//LCD_Command(0x18); //Shift entire display to the Left
	//}
	//
	//}
	//else
	//{
	//LCD_Clear();
	//LCD_String("RECEIVE SMS MSG!");
	//LCD_Command(0xC0);
	//LCD_String("ERROR Occurred!!");
	//_delay_ms(1200);
	//};
	//
	////-------------------------------------------Deleting SMS Message ----------------------------------------------------
	//LCD_Clear();
	//LCD_String("DELETING SMS MSG");
	//LCD_Command(0xC0);
	//LCD_String("SMS Deleting..!!");
	//_delay_ms(500);
	//
	//if (DelSMS(1)>0)
	//{
	//LCD_Clear();
	//LCD_String("DELETING SMS MSG");
	//LCD_Command(0xC0);
	//LCD_String("Successful...!!!");
	//_delay_ms(1200);
	//
	//}
	//else
	//{
	//LCD_Clear();
	//LCD_String("DELETING SMS MSG");
	//LCD_Command(0xC0);
	//LCD_String("ERROR Occurred!!");
	//_delay_ms(1200);
	//};
	
	
	//TxSMSviaSIM800L(AT);
	
	while(1)
	{
		UART_TxStringfromPROGMEM(AT);
		_delay_ms(1000);
	}

	return (1);
	
}// END OF MAIN PROGRAMME
//--------------------------------------------------------------------

//ISR (INT0_vect)
//{
//LCD_Clear();
//LCD_String("THIS IS INTERRUPT");
//LCD_Command(0xC0);
//LCD_String("oooOKkkkkkk");
//_delay_ms(1200);
//
//ATresponse_length = UART_RxString((char *)ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
//
//
//if (strncmp((const char *)RIresponds, "RING", sizeof("RING"))==0)
//{
///*the format of the incoming call is as:-
//<CR><LF>RING<CR><LF>
//<CR><LF>+CLIP: NUMBER,type of number,,,NAME,0<CR><LF> */
//
//ATresponse_length = UART_RxString((char *)ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
//
//for (colon_location=0; ATresponse[colon_location] !=':'; colon_location++) {RIresponds[colon_location]=ATresponse[colon_location];};
//if (strncmp((const char *)RIresponds, "+CLIP", sizeof("+CLIP"))==0)
//{
////---------------------------------------- Received CALL PHONE NUMBER --------------------------------------------------
//for (doublequote_loc=colon_location; ATresponse[doublequote_loc] !='\"'; doublequote_loc++){}; // locate (index) the First double quote'\"'
//doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the First double quote'\"'
//// Obtain the Received SMS phone number
//for (i=0; ATresponse[doublequote_loc] !='\"'; i++, doublequote_loc++) { RXcallPHONENO[i]=ATresponse[doublequote_loc]; };
//RXcallPHONENO[i]='\0'; // Terminate the RXcallPHONENO array with NULL='\0' character
//
////----------------------------------------- Received CALL PHONE NAME ----------------------------------------------------
//doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Second double quote '\"'
//while (ATresponse[doublequote_loc] !='\"') {doublequote_loc++;};// locate (index) the Third double quote '\"'
//doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Third double quote '\"'
//while (ATresponse[doublequote_loc] !='\"') {doublequote_loc++;};// locate (index) the Fourth double quote '\"'
//doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Fourth double quote '\"'
//// Obtain the Received CALL phone Name (if any)
//for (i=0; ATresponse[doublequote_loc] !='\"'; i++, doublequote_loc++)	{ RXcallPHONENAME[i]=ATresponse[doublequote_loc]; };
//RXcallPHONENAME[i]='\0'; // Terminate the RXcallPHONENAME array with NULL='\0' character
//}
//
//}
//else
//{
//for (colon_location=0; ATresponse[colon_location] !=':'; colon_location++) {RIresponds[colon_location]=ATresponse[colon_location];};
//if (strncmp((const char *)RIresponds, "+CMT", sizeof("+CMT"))==0)
//{
//
//}
//
//}
//
//}


//ch1=0;
//ch2=0;
//LCD_String("OMer Sharif ++");
//
//LCD_Command(0xc0);
//
//LCD_String("UBRRH:");
//LCD_Char(UBRRH+48);
//
//LCD_String("UBRRL:");
//LCD_Char(UBRRL+48);
//
//_delay_ms(1000);
//
//LCD_Clear();
//
//UART_TxChar(0x37);
//_delay_us(1000);
//ch1= UART_RxChar();
//LCD_String("Rx1:");
//LCD_Char(ch1);
//
//LCD_Command(0xc0);
//
//UART_TxChar('F');
//_delay_ms(1);
//ch2= UART_RxChar();
//LCD_String("Rx2:");
//LCD_Char(ch2);
//
//_delay_ms(1000);
//
//
//
//LCD_Clear();
//
//wholeline= UART_TxRxString(s,ch3);
//

//for (i=0; s[i]!=0;i++)
//{
//UART_TxChar(s[i]);
//_delay_ms(1);
//ch3[i]=UART_RxChar();
//}


//LCD_String("Res:");
//LCD_String(ch3);
//
//LCD_Command(0xc0);
//LCD_String("Len:");
//LCD_Char(wholeline+48);
//
//_delay_ms(3000);

//LCD_Clear();
//wholeline = UART_TxRxStringfromPROGMEM(AT,ch4);
//LCD_String("AT:");
//LCD_Char(pgm_read_byte(AT[0]));
//LCD_Char(pgm_read_byte(AT[1]));
//LCD_Char(pgm_read_byte(AT[2]));
//LCD_Char(pgm_read_byte(AT[3]));
//LCD_Char(pgm_read_byte(AT[4]));
//
//
//LCD_Command(0xc0);
//LCD_String("Len:");
//LCD_Char(wholeline+48);
//LCD_String("Rx:");
//LCD_String(ch4);
//

//LCD_Char(ch3[0]);
//LCD_Char(ch3[1]);
//LCD_Char(ch3[2]);
//LCD_Char(ch3[3]);
//LCD_Char(ch3[4]);
//LCD_Char(ch3[5]);

//LCD_Command(0xc0);
//
//UART_TxSTRINGfromPROGMEM(AT);
//_delay_ms(2);
//
//response_pos=0;
//
//for (i=0; ch4[i]!=0;i++)
//{
//ch4[i]=UART_RxChar();
//if (ch4[i] !='\n' && ch4[i] !='\r')
//{
//response[response_pos]=ch4[i];
//response_pos++;
//
//};
//};
//
//
//LCD_String("CH4:");
//LCD_Char(ch4[0]);
//LCD_Char(ch4[1]);
//LCD_Char(ch4[2]);
//LCD_Char(ch4[3]);
//LCD_Char(ch4[4]);
//
//LCD_String("Re:");
//LCD_Char(response_pos+48);
//
//_delay_ms(500);
//
//LCD_Clear();
//LCD_String(response);
//
//
//wholeline = 0;
//response_pos = 0;
//
//LCD_Command(0xc0);
//
//UART_TxSTRINGfromPROGMEM(OK);
//_delay_ms(2);
//
//for (i=0; ch5[i]!=0;i++)
//{
//ch5[i]=UART_RxChar();
//if (ch5[i] !='\n' && ch5[i] !='\r')
//{
//response[response_pos]=ch5[i];
//response_pos++;
//
//};
//};
//
//if (response_pos > 0)
//{
//wholeline=1;
//};
//
//LCD_Char(wholeline+48);
//LCD_Char(response_pos+48);
//_delay_ms(500);
//LCD_Clear();
//LCD_String("Re:");
//LCD_String(ch5);
////------------------------------------------------
//
//
//wholeline = 0;
//response_pos = 0;
//LCD_Clear();
//
//
//UART_TxString("AT+CPIN? \n\r");
//_delay_ms(2);
//
//int j;
//for( j=0;temp1[j]!='\0';j++)				/* Send each char of string till the NULL */
//{
//
//
//temp1[j]=UART_RxChar();
//
//};
//LCD_Command(0xc0);
//
//LCD_Char(j+48);
//
//LCD_String("Re:");
//LCD_String(temp1);

