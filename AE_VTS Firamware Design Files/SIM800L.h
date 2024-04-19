/*
 * SIM800L.h
 *
 * Created: 4/20/2020 6:36:25 PM
 *  Author: Omer
 */ 


#ifndef SIM800L_H_
#define SIM800L_H_

#include <stdlib.h> // include <stdlib.h> where General utilities are there such as atoi function


#define BUFFER_SIZE 80  // buffers for number of phone, responses from modem, longtitude & latitude data
/*--------------------------------------------------------------------------------------------
PROGRAMM MEMORY VALUES
--------------------------------------------------------------------------------------------*/
const char AT[]			PROGMEM = {"AT\r\n"};
const char ISOK[]		PROGMEM = {"OK"};
const char ECHO_OFF[]	PROGMEM = {"ATE0\r\n"};   //Echo mode off 
	
const char SETBAUD[] PROGMEM = { "AT+IPR=2400\r\n" };	// Fix UART speed to 9600 bps
const char SAVECNF[] PROGMEM = { "AT&W\r\n" };			// Save settings to SIM800L
//--------------------------------------------------------------------------------------------

// AT+CSQ Signal Quality Report
const char SIGNALQLTY[] PROGMEM = { "AT+CSQ\r\n" }; //Signal Quality Report

// AT+CCID Show ICCID
const char SIMIDCHCK[]	PROGMEM = { "AT+CCID=?\r\n" }; // Check the SIM card information 
const char SIMIDSHOW[]	PROGMEM = { "AT+CCID\r\n" }; // show the SIM card information (Show ICCID)

// AT+CFUN Set Phone Functionality by Flight-mode ON OFF - for saving battery in underground garage
const char FUNFULL[]		PROGMEM = { "AT+CFUN=1\r\n" };	// 1: Full functionality (Default)
const char FUNFLY[]			PROGMEM = { "AT+CFUN=4\r\n" };	// 4: Disable phone both transmit and receive RF circuits.
const char FUNRESETFULL[]	PROGMEM = { "AT+CFUN=1,1\r\n" };	// Reset the MT before setting it to Full functionality (Default) power level			 

// AT+CREG Network Registration
const char DISREGURC[]			PROGMEM = {"AT+CREG=0\r\n"}; // Disable network registration unsolicited result code URC to prevent coverage lost 
const char SHOW_REGISTRATION[]	PROGMEM = {"AT+CREG?\r\n"};
	
const char ISREG00[] PROGMEM = { "+CREG: 0,0" }; // Not registered, MT is NOT currently searching a new operator to register to
const char ISREG01[] PROGMEM = { "+CREG: 0,1" }; // registered in HOME network
const char ISREG02[] PROGMEM = { "+CREG: 0,2" }; // Not registered, but MT is currently searching a new operator to register to
const char ISREG03[] PROGMEM = { "+CREG: 0,3" }; // Registration denied
const char ISREG04[] PROGMEM = { "+CREG: 0,4" }; // Unknown
const char ISREG05[] PROGMEM = { "+CREG: 0,5" }; // registered in ROAMING network 
//------------------------------------------------------------------------------------------------

//AT+SAPBR Bearer Settings for Applications Based on IP
const char SAPBR_CONTYPE[]	PROGMEM = {"AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"}; // Type of Internet connection: GPRS 
const char SAPBR_APN[]		PROGMEM = {"AT+SAPBR=3,1,\"APN\",\"sudaninet\"\r\n"}; // Put your mobile operator APN name here
const char SAPBR_USER[]		PROGMEM = {"AT+SAPBR=3,1,\"USER\",\"sudani\"\r\n"}; // Put your mobile operator APN username here
const char SAPBR_PWD[]		PROGMEM = {"AT+SAPBR=3,1,\"PWD\",\"sudani\"\r\n"}; // Put your mobile operator APN password here

// PDP context commands

const char SAPBROPEN[]	PROGMEM = {"AT+SAPBR=1,1\r\n"}; // open IP bearer
const char SAPBRQUERY[] PROGMEM = {"AT+SAPBR=2,1\r\n"}; // query IP bearer
const char SAPBRCLOSE[] PROGMEM = {"AT+SAPBR=0,1\r\n"}; // close bearer

//AT Commands for HTTP Application
const char HTTPSERVERTEST[]		PROGMEM = {"AT+HTTPINIT=?\r\n"}; // AT+HTTPINIT Initialize HTTP Service TEST
const char HTTPSERVERINIT[]		PROGMEM = {"AT+HTTPINIT\r\n"}; // AT+HTTPINIT Initialize HTTP Service 
	
// AT+HTTPPARA Set HTTP Parameters Value 
const char HTTPPARACID[]		PROGMEM = {"AT+HTTPPARA=\"CID\",1\r\n"}; // AT+HTTPPARA=\"CID\",1 (Mandatory Parameter) Bearer profile identifier 
const char HTTPPARAURL[]		PROGMEM = {"AT+HTTPPARA=\"URL\",\"http://maps.google.com/maps?q=\"\r\n"}; // (Mandatory Parameter) HTTP client URL: AT+HTTPPARA="URL","http://"server"/"path":"tcpPort""

////AT+HTTPACTION HTTP Method Action
//const char HTTPACTIONGET[]			PROGMEM = {"AT+HTTPACTION=0\r\n"}; // AT+HTTPACTION=0 HTTP method specification:GET 
//const char HTTPACTIONREADTEST[]		PROGMEM = {"AT+HTTPREAD=?\r\n"}; // AT+HTTPREAD Read the HTTP Server Response TEST	
//const char HTTPACTIONREAD[]			PROGMEM = {"AT+HTTPREAD\r\n"}; // AT+HTTPREAD Read the HTTP Server Response 
	
// AT+CIPGSMLOC=1,1 GSM Location and Time
const char GSMLOC[]			PROGMEM = {"AT+CIPGSMLOC=1,1\r\n"};	// AT+CIPGSMLOC=1,1 GSM Location and Time
		
// Send SMS Commands
const char GSMCHARSET[]		PROGMEM = {"AT+CSCS=\"GSM\"\r\n"};	//AT+CSCS Select TE Character Set to "GSM" GSM 7 bit default alphabet (3GPP TS 23.038);
const char SMSTEXT[]		PROGMEM = {"AT+CMGF=1\r\n"};		//Set SMS system into text mode

const char SENDSMSCHCK[]		PROGMEM = {"AT+CMGS=?\r\n"};		//Check (TEST) the Send of SMS message
const char SENDSMSCMD[]			PROGMEM = {"AT+CMGS="};				//Send an SMS command
const char SENDSMSPHONENO[]		PROGMEM = {"\"+249964211890\""};	// Destination phone number with country code and between double quote: \"+249117778848\"

// AT+CMGR Read SMS Message
const char READSMSCHCK[]	PROGMEM = {"AT+CMGR=?\r\n"};		//Read SMS Message test command
const char READSMSCMD[]		PROGMEM = {"AT+CMGR="};				//Read SMS Message with <index> command

//AT+CMGD Delete SMS Message
const char DELSMSCHCK[]	PROGMEM = {"AT+CMGD=?\r\n"};		//Delete SMS Message test command
const char DELSMSCMD[]	PROGMEM = {"AT+CMGD="};				//Delete SMS Message with <index> command

volatile static char ATresponse[BUFFER_SIZE] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
volatile static uint8_t ATresponse_length = 0;

static char bufMEM[20]; // buffer to copy string from PROGMEM

static char longitude[12] = "123456789012"; // buffer to copy the longitude in degrees
static uint8_t longitude_length = 0;

static char latitude[12] = "123456789012";  // buffer to copy the latitude in degrees
static uint8_t latitude_length = 0;

static char date[12] = "123456789012";  // buffer to copy the date. Format is YYYY/MM/DD, the time zone is GMT E.g.2011/01/26
static uint8_t date_length = 0;

static char time[12] = "123456789012";  // buffer to copy the time.  Format is hh/mm/ss,the time zone is GMT.E.g. 06:10:46
static uint8_t time_length = 0;

static char GSMLOCATIONTIME[120]="GSM location:";

static char RXsmsSTATUS[12];
static char RXsmsPHONENO[15];
static char RXsmsPHONENAME[20];
static char RXsmsDATETIME[22];

static char RXsmsMESSAGE[120];
static uint8_t RXsmsMESSAGE_length = 0; 



/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
uint8_t CheckAT(void);
uint8_t SIMcardINFO(void);
uint8_t CheckSignalQlty(void);
uint8_t CheckSIM800Lregistration(void);
uint8_t BEARERconfiguration(uint8_t GPRS_config);
uint8_t HTTPsetup(void);
uint8_t GSMLocationTime(void);
uint8_t TxSMSviaSIM800L(char *ptr_TxSMSstring);
uint8_t RxSMSviaSIM800L(uint8_t smsINDEX);


#endif /* SIM800L_H_ */


/***************************************************************************************************
                         uint8_t CheckAT(void)
****************************************************************************************************
 * I/P Arguments:	None
 * Return value	:	uint8_t: Number of chars received.

 * description  :	SIM800L Initialization
             1.	Wait for first OK while sending AT - auto-sensing speed on SIM800L,
             2.	Set the SIM800L baud rate to 9600 bps  by: AT+IPR=9600
             3.	Save the baud rate configuration to SIM 800L by: AT&W
             4.	Turn the ECHO OFF by: ATE0
***************************************************************************************************/

uint8_t CheckAT(void)
{
	uint8_t SynchAT, SetBaud, SaveBaud, EchoOFF;
	// Continuously repeat sending AT command until the response of SIM800L is OK
	// SIM800L response is as : <CR><LF><response><CR><LF>
	SynchAT=0;
	ATresponse_length=0;
	do
	{
		UART_TxStringfromPROGMEM(AT);					//Send AT command to SIM800L
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SynchAT=1;};	// compare the SIM800L response and memory buffer for n-character
	} while (SynchAT !=1);
	
	//-----------------------------------------Set the Baud rate ------------------------------------------
	SetBaud=0;
	do
	{
		UART_TxStringfromPROGMEM(SETBAUD); // "AT+IPR=2400\r\n"   Set TE-TA Fixed Local Rate set the baud rate to baudRate
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SetBaud=1;};
	} while (SetBaud !=1);
	
	////----------------------------------Save the Baud rate Configuration ----------------------------------
	SaveBaud=0;
	do
	{
		UART_TxStringfromPROGMEM(SAVECNF);		// "AT&W\r\n": save the baud rate configuration to SIM800L
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SaveBaud=1;};
	} while (SaveBaud !=1);
	
	//---------------------------------Turn the Echo OFF------------------------------------------------------
	EchoOFF=0;
	do
	{
		UART_TxStringfromPROGMEM(ECHO_OFF);		// "ATE0\n\r" : Turn OFF the Echo at SIM800L
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {EchoOFF=1;};
	} while (EchoOFF !=1);

	if (SynchAT && SetBaud && SaveBaud && EchoOFF) { return (1);}
	else {return (0);}
	
}//-------- END OF uint8_t checkAT(void) -------------------------------------------------------------------------


/***************************************************************************************************
                         uint8_t SIMcardINFO(void)
****************************************************************************************************
 * I/P Arguments:	None
 * Return value	:	uint8_t: return the status of the SIM card if it is plugged (1) or Not (0)

 * description  :	Read SIM information to confirm whether the SIM is plugged or Not
***************************************************************************************************/

 uint8_t SIMcardINFO(void)
 {
	 uint8_t SIMCHKOK, SIMOK;
	 
	 //-------------------------------------------------  SIM CARD ID TEST COMMAND ----------------------------------------
	 SIMCHKOK=0;
	 do
	 {
		 _delay_ms(2000); // wait 2sec for Detecting the SIM card Status
		 
		 UART_TxStringfromPROGMEM(SIMIDCHCK);			// AT+CCID=? Check SIM card ID
		 ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		 memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		 if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SIMCHKOK=1;};
	 } while (SIMCHKOK !=1);
	 
	  //----------------------------------------------- CHECK SIM CARD ID ------------------------------------------------
	 SIMOK=0;
	 do
	 {
		 UART_TxStringfromPROGMEM(SIMIDSHOW);	// AT+CCID Show SIM card ID where Ccid data[ex. 898600810906F8048812]
		 ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		 if (strncmp((const char *)ATresponse, "ERROR", sizeof"ERROR")==0)
		 {
			 SIMOK=0;
			 break;
		 }
		 else {SIMOK =1;} ;
	 } while (SIMOK !=1);
	 
	 if (SIMCHKOK && SIMOK) { return (1); }
	 else { return (0);};
	 
 }//-------------- END OF SIM CARD STATUS FUNCTION -------------------------------------------------------------------------
 
 
/***************************************************************************************************
                         uint8_t CheckSignalQlty(void)
****************************************************************************************************
 * I/P Arguments:	None
 * Return value	:	uint8_t: returns received signal strength indication <rssi>: 
							0  -115 dBm or less
							1  -111 dBm
							2...30   -110... -54 dBm
							31 -52 dBm or greater
							99 not known or not detectable.

 * description  :	Signal Quality Report
***************************************************************************************************/

 uint8_t CheckSignalQlty(void)
 {
	 char sgnlQlty[12], rssi[5];
	 uint8_t SGNLERROR, SGNLQlty, RSSI, colon_location, comma_location;
	 
	 SGNLERROR=0;
	 SGNLQlty=0;
	 RSSI=0;
	 colon_location=0;
	 comma_location=0;
	 do
	 {
		 //_delay_ms(3);// wait 3sec for changing the RSSI value
		 
		 UART_TxStringfromPROGMEM(SIGNALQLTY);	// Check the Signal Quality { "AT+CSQ\r\n" }
		 ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	 
		 for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { sgnlQlty[colon_location]=ATresponse[colon_location];}; // locate the colon ':' in the ATresponse
		 
		 
		 
		 if (strncmp((const char *)sgnlQlty, (const char *)"+CSQ", colon_location)==0)
		 {
			 // When the response of execution command "AT+CSQ" is: +CSQ: <rssi>,<ber>
			 
			 colon_location=colon_location+2; // increment colon_location by 2 to find the index of the next character
			 
			 // copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
			 for (comma_location=0 ; ATresponse[colon_location]!=','; colon_location++ ,comma_location++) { rssi[comma_location]=ATresponse[colon_location];};
			 rssi[comma_location]= '\0'; // terminate the array with NULL character
			 RSSI=atoi((const char *)rssi); //atoi function Converts a string to an integer.
			 
			 LCD_Clear();
			 LCD_String("RSSI:");
			 LCD_Char((RSSI/10)+48);
			 LCD_Char((RSSI%10)+48);
			 _delay_ms(2500);
			 
			 if ((RSSI>=20) && (RSSI<99))
			 {
				 //RSSI is in a working range, therefore exit do-loop
				 SGNLQlty=1;
				 SGNLERROR=0;
			 }
			 else
			 {
				 // If there is NO ERROR and the signal quality is out of range, the function of signal quality may be repeated again
				 SGNLQlty=0;
				 SGNLERROR=0;
			 };
		 }
		 else if (strncmp((const char *)sgnlQlty, (const char *)"+CME ERROR", sizeof("+CME ERROR"))==0)
		 {
			 // If error is related to ME functionality, the response is: +CME ERROR: <err>
			 SGNLQlty=0;
			 SGNLERROR=1;
			 RSSI=0;
		 };
		 
	 } while ( (SGNLQlty==0) && (SGNLERROR==0));		// exit when there is AN ERROR  or  NO ERROR and RSSI is between 30-99
	 
	 return (SGNLQlty);
 }//-------------   END of SIGNAL QUALITY FUNCTION ----------------------------------------------------------------------------
 
 
/***************************************************************************************************
                         uint8_t CheckSIM800Lregistration(void)
****************************************************************************************************
 * I/P Arguments:	None
 * Return value	:	uint8_t: 1 for successful registration or 0 for unsuccessful registration.

 * description  :	Check if the SIM800L is registered to the GSM network
             1.	Turn the Flight Mode OFF in SIM800L,
             2.	Disable network registration unsolicited result code (URC)
             3.	Show GSM Network Registrations:
				a. return successful registration if registered in Home or Rooming network
             	b. recursive calling the checkSIM800Lregisteration until successful registration
***************************************************************************************************/

uint8_t CheckSIM800Lregistration(void)
{
	uint8_t FUNERROR, FUNON, colon_location, URCOFF, SHOWREG;
	char FUNrespnse[12];
	
	//---------------------------------Set Phone Functionality : Turn the Flight Mode OFF------------------------------------------------------
	FUNERROR=0;
	FUNON=0;
	do
	{
		UART_TxStringfromPROGMEM(FUNFULL);			// "AT+CFUN=1\r\n"  1: Full functionality (Default) i.e. Turn OFF the Flight Mode at SIM800L
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
		{
			//When the response of Write Command AT+CFUN=1 is "OK"
			FUNERROR=0;
			FUNON=1;
		}
		else
		{
			// If the response is NOT "OK" then check for ME FUNCTIONALITY ERROR: +CME ERROR: <err>
			
			// locate the colon ':' in the ATresponse
			for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { FUNrespnse[colon_location]=ATresponse[colon_location];}; 
			if (strncmp((const char *)FUNrespnse, (const char *)"+CME ERROR", colon_location)==0)
			{
				// If error is related to ME functionality, the response is as: +CME ERROR: <err>
				FUNERROR=1;
				FUNON=0;
			}
			else
			{
				// If there is NO Functionality ERROR, and the response is NOT OK, the function may need to repeated again after while
				FUNERROR=0;
				FUNON=0;
			}
		}
		
	//_delay_ms(50000); // give reasonable time (about 50sec=50% of MAX Response time) to Set Phone Functionality
	} while ((FUNERROR==0) && (FUNON ==0));
	
	//----------------Disable network registration unsolicited result code (URC)----------------------------------------
	
	URCOFF=0;
	do
	{
		UART_TxStringfromPROGMEM(DISREGURC);	// "AT+CREG=0\n\r" Disable network registration unsolicited result code URC to prevent coverage lost 
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {URCOFF=1;};
	} while (URCOFF !=1);
	
	//---------------------------------Show GSM Network Registrations-----------------------------------------------------
	
	SHOWREG=0;
	do
	{
		UART_TxStringfromPROGMEM(SHOW_REGISTRATION);	// "AT+CREG?" Show the GSM network registration status at SIM800L
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISREG01, sizeof(ISREG01)); //copy the Memory content (Registered, home network ) to the memory buffer
		
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SHOWREG=1;}
		else
		{
			memcpy_P(bufMEM, ISREG02, sizeof(ISREG02)); //copy the Memory content (NOT Registered but Searching) to the memory buffer
			
			if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
			{
				// ISREG02="+CREG: 0,2": Not registered, but MT is currently searching a new operator to register to
				//_delay_ms(60000); // Wait for 60sec to let SIM800L COMPLETE its registration
				SHOWREG= CheckSIM800Lregistration(); // recursive call for checkSIM800Lregistration() function
			}
			else
			{
				memcpy_P(bufMEM, ISREG05, sizeof(ISREG05)); //copy the Memory content (Registered, roaming ) to the memory buffer
				if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SHOWREG=1;}
				else
				{
					UART_TxStringfromPROGMEM(FUNFLY);	// Turn ON the Flight Mode at SIM800L
					//UART_TxStringfromPROGMEM(FUNRESETFULL);	// AT+CFUN=1,1 can be used to reset module purposely at minimum/full functionality mode.
					ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
					
					memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
					if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
					{
						//_delay_ms(60000); // Wait for 60sec with Flight Mode
						SHOWREG= CheckSIM800Lregistration(); // recursive call for checkSIM800Lregistration() function
					}
				}
			}
		}
		
	} while (SHOWREG !=1);
	
	if (FUNON && URCOFF && SHOWREG) {return (1);} 
	else { return (0);}

}
//------------- END OF uint8_t checkSIM800Lregistration(void) Function ------------------------------------------------


/***************************************************************************************************
uint8_t BEARERconfiguration(uint8_t GPRS_config)
****************************************************************************************************
* I/P Arguments:	uint8_t GPRS_config:	1- to OPEN the GPRS context 
											0- to CLOSE the GPRS context  
* Return value :	return 0- for ERROR or unsuccessful Configuration, 1-Successful Configuration

* description  :	AT+SAPBR Bearer Settings for Applications Based on IP
				1. Set the Internet connection: GPRS i.e. {AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"}
				2. Set the Mobile operator APN name i.e. {"AT+SAPBR=3,1,\"APN\",\"sudaninet\"\r\n"}
				3. Set the Mobile operator APN user name i.e. {"AT+SAPBR=3,1,\"USER\",\"sudani\"\r\n"}
				4. Set the Mobile operator APN Password i.e. {"AT+SAPBR=3,1,\"PWD\",\"sudani\"\r\n"}
				5. If the GPRS_config is 1 i.e OPEN: 
					a. Open IP bearer i.e. {"AT+SAPBR=1,1\r\n"};
					b. Query IP bearer {"AT+SAPBR=2,1\r\n"}; 
				6. If the GPRS_config is 0 i.e. CLOSE:  Close IP bearer i.e. {"AT+SAPBR=0,1\r\n"};	

***************************************************************************************************/
uint8_t BEARERconfiguration(uint8_t GPRS_config)
{
	
	uint8_t GPRScon, APNname, USERname, PassWRD, IPConfig, IPQuery,  colon_location;
	char IPqueryresponse[12];
	
	//----------------------------------Set Type of Internet connection: GPRS connection-------------------------------------
	
	GPRScon=0;
	do
	{
		UART_TxStringfromPROGMEM(SAPBR_CONTYPE);	// {"AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"}; Set Type of Internet connection: GPRS connection.
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {GPRScon=1;};
	} while (GPRScon !=1);
	
	//----------------------------------------Set Mobile Operator Access Point Name (APN) Name----------------------------------------------------
	
	APNname=0;
	do
	{
		UART_TxStringfromPROGMEM(SAPBR_APN);	// {"AT+SAPBR=3,1,\"APN\",\"sudaninet\"\r\n"} Set Access point Name.
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {APNname=1;};
	} while (APNname !=1);
	
	//----------------------------------------Set Mobile Operator APN User Name ----------------------------------------------------
	
	USERname=0;
	do
	{
		UART_TxStringfromPROGMEM(SAPBR_USER);	// {"AT+SAPBR=3,1,\"USER\",\"sudani\"\r\n"} Set User Name.
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {USERname=1;};
	} while (USERname !=1);
	
	//----------------------------------------Set Mobile Operator APN Password -----------------------------------------------------

	PassWRD=0;
	do
	{
		UART_TxStringfromPROGMEM(SAPBR_PWD);	// {"AT+SAPBR=3,1,\"PWD\",\"sudani\"\r\n"}; Set Password.
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {PassWRD=1;};
	} while (PassWRD !=1);
	
	//------------------------------------------ OPEN or CLOSE the GPRS ----------------------------------------------------------------
	IPConfig=0;
	if (GPRS_config==1)
	{
		//----------------------------------------- Open IP bearer --------------------------------------------------------------------
		
		do
		{
			UART_TxStringfromPROGMEM(SAPBROPEN);	// {"AT+SAPBR=1,1\r\n"}; open IP bearer
			ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
			memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
			if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {IPConfig=1;};
		} while (IPConfig !=1);
		
		//-------------------------------------------- Query IP bearer -----------------------------------------------------------------
		
		IPQuery=0;
		do
		{
			UART_TxStringfromPROGMEM(SAPBRQUERY);	// {"AT+SAPBR=2,1\r\n"}; query IP bearer
			ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
			// The response is as: +SAPBR: 1,1,"10.89.193.1"
			
			for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { IPqueryresponse[colon_location]=ATresponse[colon_location];}; // locate the colon ':' in the ATresponse
			if (strncmp((const char *)IPqueryresponse, (const char *)"+SAPBR", colon_location)==0) {IPQuery=1;};
		} while (IPQuery !=1);
		
	}
	else if (GPRS_config==0)
	{
		//----------------------------------------- CLOSE IP bearer --------------------------------------------------------------------
		do
		{
			UART_TxStringfromPROGMEM(SAPBRCLOSE);	// {"AT+SAPBR=0,1\r\n"}; Close IP bearer
			ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
			memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
			if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {IPConfig=1;};
		} while (IPConfig !=1);

	}
	
	if (GPRScon && APNname && USERname && PassWRD && IPConfig) { return (1);} 
	else { return (0);}

	
}// END of BEARER Configuration function 
	
		
/***************************************************************************************************
uint8_t HTTPsetup(void)
****************************************************************************************************
* I/P Arguments:	void
* Return value :	return 0- for ERROR or unsuccessful read to the HTTP contents, 1- for Successful read to the HTTP contents

* description  :	Setup parameters for HTTP session
				1. Initialize HTTP Service TEST i.e. {"AT+HTTPINIT=?\r\n"}; 
				2. Initialize HTTP Service: Execution Command AT+HTTPINIT i.e. {"AT+HTTPINIT\r\n"};
				3. Set HTTP Parameters Value "CID": {"AT+HTTPPARA=\"CID\",1\r\n"}; (Mandatory Parameter) Bearer profile identifier
				4. Set HTTP Parameters Value "URL": {"AT+HTTPPARA=\"URL\",\"http://maps.google.com/maps?q=\"\r\n"};  (Mandatory Parameter) HTTP client URL
				
***************************************************************************************************/	
	
uint8_t HTTPsetup(void)
{
	uint8_t HTTPserver_TEST, httpINIT, httpINITERROR, httpCID, httpCIDERROR,  httpURL, httpURLERROR, colon_location;
	char httpINITrespnse[12], httpCIDrespnse[12], httpURLrespnse[12];
	
	//-------------------------------  Initialize HTTP Service TEST i.e. -----------------------------------
	HTTPserver_TEST=0;
	do
	{
		UART_TxStringfromPROGMEM(HTTPSERVERTEST);	// {"AT+HTTPINIT=?\r\n"}; // AT+HTTPINIT Initialize HTTP Service TEST
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {HTTPserver_TEST=1;};
	} while (HTTPserver_TEST !=1);
	
	//-------------------------------  Initialize HTTP Service: Execution Command AT+HTTPINIT -----------------------------------
	
	httpINIT=0;
	httpINITERROR=0;
	do
	{
		UART_TxStringfromPROGMEM(HTTPSERVERINIT);	// {"AT+HTTPINIT,1\r\n"}; (Mandatory Parameter) Bearer profile identifier
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"

		memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
		{
			//When the response of Write Command "AT+HTTPINIT" is "OK"
			httpINIT=1;
			httpINITERROR=0;
		}
		else
		{
			// If the response is NOT "OK" then check for ME FUNCTIONALITY ERROR: +CME ERROR: <err>
			
			for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { httpINITrespnse[colon_location]=ATresponse[colon_location];}; // locate the colon ':' in the ATresponse
			if (strncmp((const char *)httpINITrespnse, (const char *)"+CME ERROR", colon_location)==0)
			{
				// If error is related to ME functionality, the response is as: +CME ERROR: <err>
				httpINIT=0;
				httpINITERROR=1;
			}
			else
			{
				// If there is NO Functionality ERROR, and the response is NOT OK, the function may need to repeated again after while
				httpINIT=0;
				httpINITERROR=0;
			};
		};
		
	} while ((httpINIT ==0) && (httpINITERROR==0));
	
	//----------------Set HTTP Parameters Value: 1. "CID": (Mandatory Parameter) Bearer profile identifier -----------------------------
	httpCID=0;
	httpCIDERROR=0;
	do
	{
		UART_TxStringfromPROGMEM(HTTPPARACID);	// {"AT+HTTPPARA=\"CID\",1\r\n"}; (Mandatory Parameter) Bearer profile identifier
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"

		memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
		{
			//When the response of Write Command "AT+HTTPPARA=\"CID\",1 is "OK"
			httpCIDERROR=0;
			httpCID=1;
		}
		else
		{
			// If the response is NOT "OK" then check for ME FUNCTIONALITY ERROR: +CME ERROR: <err>
			
			for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { httpCIDrespnse[colon_location]=ATresponse[colon_location];}; // locate the colon ':' in the ATresponse
			if (strncmp((const char *)httpCIDrespnse, (const char *)"+CME ERROR", colon_location)==0)
			{
				// If error is related to ME functionality, the response is as: +CME ERROR: <err>
				httpCIDERROR=1;
				httpCID=0;
			}
			else
			{
				// If there is NO Functionality ERROR, and the response is NOT OK, the function may need to repeated again after while
				httpCIDERROR=0;
				httpCID=0;
			};
		};
		
	} while ((httpCID ==0) && (httpCIDERROR==0));
	
	//----------------Set HTTP Parameters Value: 2. "URL": (Mandatory Parameter) HTTP client URL -----------------------------
	httpURL=0;
	httpURLERROR=0;
	do
	{
		UART_TxStringfromPROGMEM(HTTPPARAURL);	// {"AT+HTTPPARA=\"URL\",\"http://maps.google.com/maps?q=\"\r\n"};  (Mandatory Parameter) HTTP client URL
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"

		memcpy_P(bufMEM, ISOK, sizeof(ISOK));			//copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
		{
			//When the response of Write Command "AT+HTTPPARA=\"URL\",1 is "OK"
			httpURLERROR=0;
			httpURL=1;
		}
		else
		{
			// If the response is NOT "OK" then check for ME FUNCTIONALITY ERROR: +CME ERROR: <err>
			
			for (colon_location=0; ATresponse[colon_location]!=':'; colon_location++) { httpURLrespnse[colon_location]=ATresponse[colon_location];}; // locate the colon ':' in the ATresponse
			if (strncmp((const char *)httpURLrespnse, (const char *)"+CME ERROR", colon_location)==0)
			{
				// If error is related to ME functionality, the response is as: +CME ERROR: <err>
				httpURLERROR=1;
				httpURL=0;
			}
			else
			{
				// If there is NO Functionality ERROR, and the response is NOT OK, the function may need to repeated again after while
				httpURLERROR=0;
				httpURL=0;
			};
		};
		
	} while ((httpURL==0) && (httpURLERROR==0));
	
	if (HTTPserver_TEST && httpINIT && httpCID && httpURL){ return (1);}
	else { return (0);};
	
	
}// END OF Download data from HTTP server i.e. HTTPGETmethod(void) function
	

/***************************************************************************************************
uint8_t GSMLocationTime(void)
****************************************************************************************************
* I/P Arguments:	void
* Return value :	return 0- for ERROR or unsuccessful read for the location and time, 1- for Successful GSM location and time

* description  : READ GSM Location (latitude and longitude) and Time using AT+CIPGSMLOC
Get location: 
Syntax:			AT+CIPGSMLOC=1,1 
Expect Result :	+CIPGSMLOC:	0,121.354848,31.221402,2011/01/26,02:41:06
				OK 

***************************************************************************************************/
uint8_t GSMLocationTime(void)
{
	char LOCresponse[12]="123456789012", locationcode[7]="1234567";
	uint8_t LOCCODE, LOCERROR,  colon_location, comma_location, LOCATIONcode;
	
	
	LOCCODE=0;
	LOCERROR=0;
	colon_location=0;
	comma_location=0;
	LOCATIONcode=0;
	
	do
	{
		UART_TxStringfromPROGMEM(GSMLOC);	// AT+CIPGSMLOC=1,1 GSM Location and Time
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		
		// Obtain the response if it is +CIPGSMLOC or +CME ERROR
		for (colon_location=0; ATresponse[colon_location] !=':'; colon_location++) { LOCresponse[colon_location]=ATresponse[colon_location];};
		LOCresponse[colon_location]='\0';// terminate the LOCresponse with NULL character='\0'
		
		LCD_Clear();
		LCD_String("LOC:");
		LCD_String(LOCresponse);
		LCD_Command(0xC0);
		LCD_String("colon:");
		LCD_Char((colon_location/10)+48);
		LCD_Char((colon_location%10)+48);
		_delay_ms(500);
		
		if (strncmp((const char *)LOCresponse, "+CIPGSMLOC", colon_location)==0)
		{
			
			colon_location=colon_location+2; // increment colon_location by 2 to find the index of the next character
			
			// copy the locationcode value at the SIM800L response: +CIPGSMLOC:<locationcode>[,<longitude>,<latitude>,<date>,<time>]
			for (comma_location=0 ; ATresponse[colon_location]!=','; colon_location++ ,comma_location++) {locationcode[comma_location]=ATresponse[colon_location];};
			locationcode[comma_location]='\0';
			
			LOCATIONcode=atoi((const char *)locationcode); //atoi function Converts a string to an integer.
			
			LCD_Clear();
			LCD_String("LOCcode:");
			LCD_Char(LOCATIONcode+48);
			LCD_Command(0xC0);
			LCD_String("comma:");
			LCD_Char((comma_location/10)+48);
			LCD_Char((comma_location%10)+48);
			_delay_ms(500);
			
			if (LOCATIONcode==0)
			{
				LOCCODE=1;
				LOCERROR=0;
							
				comma_location=colon_location;
				
				////------------------------------------- Build The GSMLOCATIONTIME array  ------------------------------------------
				//colon_location++;
				//for (i=13 ; i<=ATresponse_length; i++, colon_location++)
				//{
					//GSMLOCATIONTIME[i]=ATresponse[colon_location];		// copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
				//};
				//GSMLOCATIONTIME[i]='\0'; // Terminate the GSMLOCATIONTIME array with NULL='\0' character
				//
				//------------------------------------- READ LONGITUDE VALUE ------------------------------------------
				
				comma_location++; // increment colon_location  to find the index of the next character of FIRST COMMA','
				// copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
				for (longitude_length=0 ; ATresponse[comma_location]!=','; comma_location++ ,longitude_length++) {longitude[longitude_length]=ATresponse[comma_location];};
				longitude[longitude_length]='\0'; // Terminate the longitude array with NULL='\0' character
				
				//LCD_Clear();
				//LCD_String("LON:");
				//LCD_String(longitude);
				//LCD_Command(0xC0);
				//LCD_String("Len:");
				//LCD_Char((longitude_length/10)+48);
				//LCD_Char((longitude_length%10)+48);
				//_delay_ms(500);
				
				//------------------------------------- READ LATITUDE VALUE ---------------------------------------------
				
				comma_location++; // increment colon_location  to find the index of the next character of SECOND COMMA','
				// copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
				for (latitude_length=0 ; ATresponse[comma_location]!=','; comma_location++ ,latitude_length++) { latitude[latitude_length]=ATresponse[comma_location];};
				latitude[latitude_length]='\0'; // Terminate the latitude array with NULL='\0' character
				
				//LCD_Clear();
				//LCD_String("LAT:");
				//LCD_String(latitude);
				//LCD_Command(0xC0);
				//LCD_String("Len:");
				//LCD_Char((latitude_length/10)+48);
				//LCD_Char((latitude_length%10)+48);
				//_delay_ms(500);
				
				//------------------------------------- READ DATE VALUE ---------------------------------------------
				
				comma_location++; // increment colon_location  to find the index of the next character of THIRD COMMA','
				
				// copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
				for (date_length=0 ; ATresponse[comma_location]!=','; comma_location++ ,date_length++) {date[date_length]=ATresponse[comma_location];};
				date[date_length]='\0'; // Terminate the date array with NULL='\0' character
				
				//LCD_Clear();
				//LCD_String("Date:");
				//LCD_String(date);
				//LCD_Command(0xC0);
				//LCD_String("Len:");
				//LCD_Char((date_length/10)+48);
				//LCD_Char((date_length%10)+48);
				//_delay_ms(500);
				
				//------------------------------------- READ TIME VALUE ---------------------------------------------
				
				comma_location++; // increment colon_location  to find the index of the next character of FORTH COMMA','
				
				// copy the rssi value at the SIM800L response: +CSQ: <rssi>,<ber>  to rssi matrix
				for (time_length=0 ; comma_location<=ATresponse_length; comma_location++ ,time_length++) { time[time_length]=ATresponse[comma_location];};
				time[time_length]='\0'; // Terminate the time array with NULL='\0' character
				
				//LCD_Clear();
				//LCD_String("Time:");
				//LCD_String(time);
				//LCD_Command(0xC0);
				//LCD_String("Len:");
				//LCD_Char((time_length/10)+48);
				//LCD_Char((time_length%10)+48);
				//_delay_ms(500);
				//
				//LCD_Clear();
				//LCD_String("LOCCODE:");
				//LCD_Char(LOCCODE+48);
				//LCD_Command(0xC0);
				//LCD_String("LOCERROR:");
				//LCD_Char(LOCERROR+48);
				//_delay_ms(500);
			}
			else
			{
				LOCCODE=0;
				LOCERROR=0;
				
				//LCD_Clear();
				//LCD_String("LOCCODE:");
				//LCD_Char(LOCCODE+48);
				//LCD_Command(0xC0);
				//LCD_String("LOCERROR:");
				//LCD_Char(LOCERROR+48);
				//_delay_ms(500);
				
			}// END of if-else (LOCATIONcode==0)
		}
		else if (strncmp((const char *)LOCresponse, "+CME ERROR", colon_location)==0)
		{
			//If error is related to ME functionality: the response is as:	+CME ERROR:<err>
			LOCCODE=0;
			LOCERROR=1;
		} // END OF if-else (strncmp((const char *)LOCresponse, "+CIPGSMLOC", colon_location)==0)
		
	} while ((LOCCODE==0) && (LOCERROR==0));
	

	return(LOCCODE);
	
}//END OF uint8_t GSMLOCATIONTIME(void) Function



/***************************************************************************************************
                         uint8_t TxSMSviaSIM800L(char *ptr_TxSMSstring)
****************************************************************************************************
 * I/P Arguments:	char *:  Address of the transmitted SMS string
 * Return value	:	uint8_t: 1 for successful transmission or 0 for unsuccessful transmission.

 * description  :	Send SMS procedure:
             1. Set the Character set to "GSM"	
			 2. Set SMS system into text mode: AT+CMGF=1
			 3. Set the SMS Characters in "GSM" setting (the default setting)
             4.	Send AT command for SMS with the receiver phone number: "AT+CMGS=\"+249117778848\""
			 5. Send the Carriage Return: \r
			 6. Send SMS in (ptr_TxSMSstring) via SIM800L 
			 7. End the SMS with <Ctrl+Z>
			 8. check whether the SMS is send successfully or not  
***************************************************************************************************/

uint8_t TxSMSviaSIM800L(char *ptr_TxSMSstring)
{
	uint8_t CHARSET, SMS2TEXTmode, SendSMScheck, SendSMS, SMSERROR, colon_location;
	char smsATresponse[6];
	
	//---------------------------------Select TE Character Set------------------------------------------------------	
	CHARSET=0;
	do
	{
		UART_TxStringfromPROGMEM(GSMCHARSET);	//  AT+CSCS="GSM" Select TE Character Set to the default set "GSM"
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {CHARSET=1;};
	} while (CHARSET !=1);
	
	//---------------------------------Set SMS system into text mode------------------------------------------------------
	SMS2TEXTmode=0;
	do
	{
		UART_TxStringfromPROGMEM(SMSTEXT);	// {"AT+CMGF=1\r\n"};	Set SMS system into text mode
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SMS2TEXTmode=1;};
	} while (SMS2TEXTmode !=1);
	
	//---------------------------------Send SMS Message Check------------------------------------------------------	
	SendSMScheck=0;
	do
	{
		UART_TxStringfromPROGMEM(SENDSMSCHCK);	// "AT+CMGS=?" Check Command for SMS message
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SendSMScheck=1;};
	} while (SendSMScheck !=1);
	
	//---------------------------------Send SMS via SIM800L---------------------------------------------------------------	
	SendSMS=0;
	SMSERROR=0;
	do
	{
		UART_TxStringfromPROGMEM(SENDSMSCMD);	// "AT+CMGS=" Send AT command for SMS sending
		UART_TxStringfromPROGMEM(SENDSMSPHONENO);	// Send the destination phone number followed by carriage return: \r
		UART_TxChar('\r');					// Send the Carriage Return: \r
		UART_TxString(ptr_TxSMSstring);		// Send The contents of the SMS Message
		UART_TxChar(0x1A);					// Send <Ctrl+Z>=0x1A= 26 which is the end of the SMS
		
			
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		
		// copy the ATresponse to smsATresponse which is: +CMGS: <mr> or +CMS ERROR: <err>
		for (colon_location=0; ATresponse[colon_location] !=':'; colon_location++) {smsATresponse[colon_location]=ATresponse[colon_location];};
		
		if (strncmp((const char *)smsATresponse, "+CMGS", colon_location)==0)
		{
			// If text mode(+CMGF=1) and sending successful: +CMGS: <mr>
			SendSMS=1;
			SMSERROR=0;
		}
		else if (strncmp((const char *)smsATresponse, "+CMS ERROR", colon_location)==0)
		{
			//If error is related to ME functionality: 	+CMS ERROR: <err>
			SendSMS=0;
			SMSERROR=1;
		} else
		{
			// where there is NO ERROR and the SMS is NOT SEND, the SEND SMS procedure need to be looped again
			SendSMS=0;
			SMSERROR=0;
		};
		
	} while ((SendSMS ==0) && (SMSERROR==0));
	
	if (CHARSET && SMS2TEXTmode && SendSMScheck && SendSMS ){ return(1);}
	else {return (0);};
 
}// END OF SEND SMS MESSAGE FUNCTION: uint8_t TxSMSviaSIM800L(char *ptr_TxSMSstring)


/***************************************************************************************************
			uint8_t RxSMSviaSIM800L(uint8_t smsINDEX)
****************************************************************************************************
* I/P Arguments:	uint8_t: SMS index
* Return value :	return 0- for ERROR or unsuccessful SMS reception, 1- for Successful SMS reception

* description  :	Receive SMS procedure:
				1.	Set SMS system into text mode: AT+CMGF=1
				2.	Send a Test Command AT+CMGR=? which its response is OK
				3.  Send AT Command for reading SMS: AT+CMGR=<smsINDEX_ASCII>:
					a. convert the smsINDEX to ASCII using atoi() function
					b. send AT+CMGR=<smsINDEX_ASCII> 
					c. End this AT command with Carriage return '\r'
				4. Receive the SIM800L response which is either:
					+CMGR: "REC UNREAD","+8613918186089", "","02/01/30,20:40:31+00"<CR><LF>
					This is a test
					OK 
					
					or +CMS ERROR:<err>. 
				   If it is +CMGR then proceed for SMS reading ELSE ERROR is occurred i.e. +CMS ERROR:<err> 
				5. Locate the 1st '\"' to read the SMS STATUS: "REC READ" or "REC UNREAD"
				6. Locate the 3rd '\"' to read the SMS sender phone number
				7. Locate the 5th '\"' to read the SMS sender name
				8. Locate the 7th '\"' to read the SMS date and time
				9. Locate the Line Feed '\n' to read the SMS message (data)
				10. End reading the SMS message by <CtrlZ> 
***************************************************************************************************/
uint8_t RxSMSviaSIM800L(uint8_t smsINDEX)
{
	char RXsmsPREFIX[6], smsINDEX_ASCII[5], RXsmsResponse[120], data; // smsINDEX_ASCII[5]: create a buffer for the ASCII string
	uint8_t i, len, colon_location, doublequote_loc, SMS2TEXTmode, RXSMSTEST, RXSMS, SMSERROR;
	
	//---------------------------------Set SMS system into text mode------------------------------------------------------
	SMS2TEXTmode=0;
	do
	{
		UART_TxStringfromPROGMEM(SMSTEXT);	// {"AT+CMGF=1\r\n"};	Set SMS system into text mode
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {SMS2TEXTmode=1;};
	} while (SMS2TEXTmode !=1);
	
	//---------------------------------Test Command AT+CMGR=? ------------------------------------------------------
	RXSMSTEST=0;
	do
	{
		UART_TxStringfromPROGMEM(READSMSCHCK);	// Test Command: AT+CMGR=? Response: "OK"
		ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {RXSMSTEST=1;};
	} while (RXSMSTEST !=1);
	
	//------------------------Read SMS with index: smsINDEX by Sending AT+CMGR= <smsINDEX_ASCII> -------------------
	i=0;
	RXSMS=0;
	SMSERROR=0;
	do
	{
		itoa(smsINDEX, smsINDEX_ASCII,10);		//convert the integer (smsINDEX) to an ASCII string (smsINDEX_ASCII) in base of 10 (decimal)
		UART_TxStringfromPROGMEM(READSMSCMD);	// Send "AT+CMGR=" Read SMS command
		while (smsINDEX_ASCII[i])
		{
			UART_TxChar(smsINDEX_ASCII[i]);		// Send the SMS index in ASCII format
			i++;
		}
		UART_TxString("\r\n"); // Send carriage return: \r and Line Feed \n
		
		//---------------------------------------------------------------------------------------------------------------
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
				RXsmsResponse[len]=data; //copy the char into string and increment the index
				len++;
			} while (data !='\n') ;
			
			//data=UART_RxChar();		//Receive the next char of CR which is LF
			//ATresponse[ATresponse_length]=data; //copy the char into string and increment the index
			//ATresponse_length++;
			
			do
			{
				data=UART_RxChar();		//Receive a char
				RXsmsResponse[len]=data; //copy the char into string and increment the index
				len++;
			} while ((data !='\r') && (data !='\n') ) ;
			
			
			RXsmsResponse[len-1]='\0';  // null='\n'=0 terminate the string
		}
		//--------------- END of reading the response of Received SMS message -----------------------------
		
		LCD_Clear();
		LCD_String(RXsmsResponse);
		LCD_Command(0xC0);
		LCD_Char(len/10 +48);
		LCD_Char(len%10 +48);
		_delay_ms(1200);
		
		
		
		// copy the ATresponse to smsATresponse which is: +CMGR: <x>,<x>,<xxx> or +CMS ERROR: <err>
		for (colon_location=0; RXsmsResponse[colon_location] !=':'; colon_location++) {RXsmsPREFIX[colon_location]=RXsmsResponse[colon_location];};
		
		LCD_Clear();
		LCD_String(RXsmsPREFIX);
		LCD_Command(0xC0);
		LCD_Char(colon_location/10 +48);
		LCD_Char(colon_location%10 +48);
		_delay_ms(1200);
		
		
		if (strncmp((const char *)RXsmsPREFIX, "+CMGR", colon_location)==0)
		{
			// If text mode(+CMGF=1) and receiving successful: +CMGR: <x>,<x>,<xxx>
			RXSMS=1;
			SMSERROR=0;
			//--------------------------------------- Received SMS STATUS --------------------------------------------------------
			for (doublequote_loc=colon_location; RXsmsResponse[doublequote_loc] !='\"'; doublequote_loc++){}; // locate (index) the First double quote'\"'
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the First '\"'
			// Obtain the SMS status either "REC READ" or "REC UNREAD"
			for (i=0; RXsmsResponse[doublequote_loc] !='\"'; i++, doublequote_loc++) { RXsmsSTATUS[i]=RXsmsResponse[doublequote_loc]; };
			RXsmsSTATUS[i]='\0'; // Terminate the RXsmsSTATUS array with NULL='\0' character
			
			LCD_Clear();
			LCD_String(RXsmsSTATUS);
			LCD_Command(0xC0);
			LCD_Char(i/10 +48);
			LCD_Char(i%10 +48);
			_delay_ms(1200);
			//---------------------------------------- Received SMS PHONE NUMBER --------------------------------------------------
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Second double quote'\"'
			while (RXsmsResponse[doublequote_loc] !='\"') {doublequote_loc++;};// locate (index) the Third double quote'\"'
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Third double quote '\"'
			// Obtain the Received SMS phone number
			for (i=0; RXsmsResponse[doublequote_loc] !='\"'; i++, doublequote_loc++) { RXsmsPHONENO[i]=RXsmsResponse[doublequote_loc]; };
			RXsmsPHONENO[i]='\0'; // Terminate the RXsmsPHONENO array with NULL='\0' character
			LCD_Clear();
			LCD_String(RXsmsPHONENO);
			LCD_Command(0xC0);
			LCD_Char(i/10 +48);
			LCD_Char(i%10 +48);
			_delay_ms(1200);
			//----------------------------------------- Received SMS PHONE NAME ----------------------------------------------------
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Fourth double quote '\"'
			while (RXsmsResponse[doublequote_loc] !='\"') {doublequote_loc++;};// locate (index) the Fifth double quote '\"'
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Fifth double quote '\"'
			// Obtain the Received SMS phone Name (if any)
			for (i=0; RXsmsResponse[doublequote_loc] !='\"'; i++, doublequote_loc++)	{ RXsmsPHONENAME[i]=RXsmsResponse[doublequote_loc]; };
			RXsmsPHONENAME[i]='\0'; // Terminate the RXsmsPHONENAME array with NULL='\0' character
			LCD_Clear();
			LCD_String(RXsmsPHONENAME);
			LCD_Command(0xC0);
			LCD_Char(i/10 +48);
			LCD_Char(i%10 +48);
			_delay_ms(1200);
			//-------------------------------------------Received SMS DATE and TIME ------------------------------------------------
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Fifth double quote '\"'
			while (RXsmsResponse[doublequote_loc] !='\"') {doublequote_loc++;};// locate (index) the Sixth double quote '\"'
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Sixth double quote '\"'
			// Obtain the Received SMS time and date
			for (i=0; RXsmsResponse[doublequote_loc] !='\"'; i++, doublequote_loc++)	{ RXsmsDATETIME[i]=RXsmsResponse[doublequote_loc]; };
			RXsmsDATETIME[i]='\0'; // Terminate the RXsmsDATETIME array with NULL='\0' character
			LCD_Clear();
			LCD_String(RXsmsDATETIME);
			LCD_Command(0xC0);
			LCD_Char(i/10 +48);
			LCD_Char(i%10 +48);
			_delay_ms(1200);
			
			LCD_Clear();
			LCD_Command(0xC0);
			LCD_Char((doublequote_loc/10) +48);
			LCD_Char((doublequote_loc%10) +48);
			_delay_ms(1200);
			//------------------------------------------Received SMS MESSAGE (data)---------------------------------------------------
			// Locate the the Line Feed <LF> character looking for the <data> where the response as: xxxxxx <CR><LF><data>
			doublequote_loc++; // Increment doublequote_loc to get the index of the next character to the Seventh double quote '\"'
			while (RXsmsResponse[doublequote_loc] !='\n') { doublequote_loc++; };// locate (index) the <LF>='\n'
			doublequote_loc++; // Increment doublequote_loc to get the index of the First character in <data> which comes after <LF>='\n'
			// Obtain the received SMS message which is ended by 0x1A=<Ctrl+Z>
			
			LCD_Clear();
			LCD_Command(0xC0);
			LCD_Char((doublequote_loc/10) +48);
			LCD_Char((doublequote_loc%10) +48);
			_delay_ms(1200);
			
			for (RXsmsMESSAGE_length=0; doublequote_loc <= len; RXsmsMESSAGE_length++, doublequote_loc++)	{ RXsmsMESSAGE[RXsmsMESSAGE_length]=RXsmsResponse[doublequote_loc]; };
			RXsmsMESSAGE[RXsmsMESSAGE_length]='\0'; // Terminate the received message array with NULL='\0' character
			LCD_Clear();
			LCD_String(RXsmsMESSAGE);
			LCD_Command(0xC0);
			LCD_Char(RXsmsMESSAGE_length/10 +48);
			LCD_Char(RXsmsMESSAGE_length%10 +48);
			_delay_ms(1200);
			
		}
		else if (strncmp((const char *)RXsmsPREFIX, "+CMS ERROR", colon_location)==0)
		{
			//If error is related to ME functionality: 	+CMS ERROR: <err>
			RXSMS=0;
			SMSERROR=1;
		} else
		{
			// where there is NO ERROR and the SMS is NOT RECEIVED, the RECEIVED SMS procedure need to be looped again
			RXSMS=0;
			SMSERROR=0;
		};
	} while ((RXSMS ==0) && (SMSERROR==0));
	
	
	if (SMS2TEXTmode && RXSMSTEST && RXSMS ){ return(1);}
	else {return (0);};

}// END OF uint8_t RxSMSviaSIM800L(uint8_t smsINDEX)


/***************************************************************************************************
                         uint8_t DelSMS(uint8_t smsINDEX)
****************************************************************************************************
 * I/P Arguments:	uint8_t: SMS index
 * Return value :	return 0- for ERROR or unsuccessful SMS deletion, 1- for Successful SMS deletion

 * description  :	Delete SMS Message procedure:
          // AT+CMGD Delete SMS Message
***************************************************************************************************/

 uint8_t DelSMS(uint8_t smsINDEX)
 {
	 uint8_t DELSMSTEST, DELSMS, SMSERROR, colon_location, i;
	 char DELsmsATresponse[12], smsINDEX_ASCII[5];
	 
	 //---------------------------------Test Command AT+CMGD=? ------------------------------------------------------
	 DELSMSTEST=0;
	 do
	 {
		 UART_TxStringfromPROGMEM(DELSMSCHCK);	// Test Command: AT+CMGD=? Response: "OK"
		 ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		 memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		 if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {DELSMSTEST=1;};
	 } while (DELSMSTEST !=1);
	 
	 //-------------------------------- Delete SMS Write Command: AT+CMGD=<index>[,<delflag>] ------------------------------
	 DELSMS=0;
	 SMSERROR=0;
	 do
	 {
		 itoa(smsINDEX, smsINDEX_ASCII,10);	//convert the integer (smsINDEX) to an ASCII string (smsINDEX_ASCII) in base of 10 (decimal)
		 UART_TxStringfromPROGMEM(DELSMSCMD);	// Send "AT+CMGD=" Delete SMS command
		 i=0;
		 while (smsINDEX_ASCII[i])
		 {
			 UART_TxChar(smsINDEX_ASCII[i]);// Send the SMS index in ASCII format
			 i++;
		 }
		 UART_TxString("\r\n");				// Send carriage return: \r and Line Feed \n
		 
		 // Response: OK or +CMS ERROR:<err>
		 ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
		 memcpy_P(bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content to the memory buffer
		 
		 if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0)
		 {
			 DELSMS=1;
			 SMSERROR=0;
		 }
		 else
		 {
			 for (colon_location=0; ATresponse[colon_location] !=':'; colon_location++) {DELsmsATresponse[colon_location]=ATresponse[colon_location];};
			 if (strncmp((const char *)DELsmsATresponse, "+CMS ERROR", colon_location)==0)
			 {
				 DELSMS=0;
				 SMSERROR=1;
			 }
			 else
			 {
				 DELSMS=0;
				 SMSERROR=0;
			 }
		 }
		 
	 } while ((DELSMS ==0) && (SMSERROR==0));
	 
	 if (DELSMSTEST && DELSMS) { return(1); }
	 else { return(0); }
	 
 }// -------END of Delete SMS Message with function: uint8_t DelSMS(uint8_t smsINDEX)



	//--------------------- Getting the contents of a web page from the server -----------------
	//
	
		
		//uint8_t serverMODE, httpCID, httpGET, httpURL, httpREADTEST, httpREAD ;
		//int HTTPresponse_length;
	
	
	////------------------------------- AT+HTTPINIT Initialize HTTP Service -----------------------------------
	//serverMODE=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPSERVERINIT);	// AT+HTTPINIT Initialize HTTP Service
	//ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	//memcpy_P((const char *)bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
	//if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {serverMODE=1;}
	//else{
	//for (i=0; ATresponse[i] !=':'; i++)
	//{
	//serverERROR[i]=ATresponse[i] ; // Obtain the ERROR message
	//};
	//
	//if (strncmp((const char *)serverERROR,"+CME ERROR", sizeof("+CME ERROR"))==0) {serverMODE=0;}
	//}
	//
	//} while (serverMODE !=1);
	//
	//
	////-------------------------------Set HTTP Parameters Value  -----------------------------------
	//httpCID=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPPARACID);	// Setting up the HTTP bearer profile identifier
	//ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	//memcpy_P((const char *)bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
	//if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {httpCID=1;}
	//else{
	//for (i=0; ATresponse[i] !=':'; i++)
	//{
	//serverERROR[i]=ATresponse[i] ; // Obtain the ERROR message
	//};
	//
	//if (strncmp((const char *)serverERROR,"+CME ERROR", sizeof("+CME ERROR"))==0) {httpCID=0;}
	//}
	//
	//} while (httpCID !=1);
	//
	////------------------------ Set the URL  to the address of the web page you want to access -------------------
	//httpURL=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPPARAURL);	// Setting up the HTTP URL (Mandatory Parameter) HTTP client URL: AT+HTTPPARA= "http://'server'/'path':'tcpPort'"
	//ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	//memcpy_P((const char *)bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
	//if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0) {httpURL=1;}
	//else{
	//for (i=0; ATresponse[i] !=':'; i++)
	//{
	//serverERROR[i]=ATresponse[i] ; // Obtain the ERROR message
	//};
	//
	//if (strncmp((const char *)serverERROR,"+CME ERROR", sizeof("+CME ERROR"))==0) {httpURL=0;}
	//}
	//
	//} while (httpURL !=1);
	//
	////------------------------------------ Start the HTTP GET session -------------------------------------------
	//httpGET=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPACTIONGET);	// AT+HTTPACTION=0 Start the HTTP GET session
	//ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	//memcpy_P((const char *)bufMEM, ISOK, sizeof(ISOK)); //copy the Memory content i.e. OK to the memory buffer
	//if (strncmp((const char *)ATresponse, (const char *)bufMEM, ATresponse_length)==0){	httpGET=1;}
	//else{
	//for (i=0; ATresponse[i] !=':'; i++)
	//{
	//serverERROR[i]=ATresponse[i] ; // Obtain the ERROR message
	//};
	//
	//if (strncmp((const char *)serverERROR,"+CME ERROR", sizeof("+CME ERROR"))==0) {httpGET=0;}
	//}
	//
	//} while (httpGET !=1);
	//
	////----------------------------------- Read the data of http server TEST ---------------------------------
	//httpREADTEST=0;
	//i=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPACTIONREADTEST);	// AT+HTTPREAD=? test of Read the HTTP Server Response
	//ATresponse_length = UART_RxString(ATresponse);	// Receive the response of SIM800L in "ATresponse" and its length "ATresponse_length"
	//for (i=0; ATresponse[i] !=':'; i++)
	//{
	//httpREADresponse[i]=ATresponse[i] ; // Obtain the response: +HTTPREAD
	//};
	//
	//if (strncmp((const char *)httpREAD, "+HTTPREAD", sizeof("+HTTPREAD"))==0)
	//{
	//i=i+2; // Increment the location of ':' by 2 to find the index of <start_address>
	//
	//for (j=0; ATresponse[i] !=','; i++, j++)
	//{
	//start_address[j]=ATresponse[i] ; // Obtain the <start_address>: The starting point for data output which is 0-319488 (bytes)
	//};
	//
	//i++; // Increment the location of ',' to find the index of <byte_size>
	//
	//for (j=0; ATresponse[i] !='\0'; i++, j++)
	//{
	//byte_size[j]=ATresponse[i] ; // Obtain the <byte_size>: The length for data output which is 1-319488 (bytes)
	//};
	//httpREADTEST=1;
	//}
	//else {httpREADTEST=0;};
	//
	//} while (httpREADTEST !=1);
	//
	//
	////----------------------------------- Read the data of http server  ---------------------------------
	//httpREAD=0;
	//i=0;
	//do
	//{
	//UART_TxStringfromPROGMEM(HTTPACTIONREAD);	// AT+HTTPREAD Read the HTTP Server Response
	//HTTPresponse_length = UART_RxStringFULL(HTTPresponse);	// Receive the FULL response of SIM800L in "HTTPresponse" and its length "HTTPresponse_length"
	//for (i=0; HTTPresponse[i] !=':'; i++)
	//{
	//httpREADresponse[i]=HTTPresponse[i] ; // Obtain the response of HTTP server: +HTTPREAD
	//};
	//
	//if (strncmp((const char *)httpREADresponse, "+HTTPREAD", sizeof("+HTTPREAD"))==0)
	//{
	//i=i+2; // Increment the location of ':' by 2 to find the index of <data_len>
	//
	//for (j=0; HTTPresponse[i] !='\r'; i++, j++)
	//{
	//data_len[j]=HTTPresponse[i] ; // Obtain the <data_len>: The actual length for data output which is 1-319488 (bytes)
	//};
	//
	//i=i+2; // Increment the location of '\r' by 2 to find the index of <data>
	//
	//for (j=0; i < HTTPresponse_length-2; i++, j++)
	//{
	//httpDATA[j]=HTTPresponse[i] ; // Obtain the <data>: Data from HTTP server
	//};
	//httpREAD=1;
	//}
	//else if (strncmp((const char *)httpREADresponse, "+CME ERROR", sizeof("+CME ERROR"))==0) {httpREAD=0;};
	//
	//} while (httpREAD !=1);
	//
	//return (GPRSsetting);
	
	
	//}// END OF GPRSforIPAPS