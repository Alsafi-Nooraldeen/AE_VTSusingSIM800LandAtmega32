/***************************************************************************************************
                                   ExploreEmbedded    
*****************************************************************************************************
 * File:   lcd.h
 * Version: 1.0
 * Author: ALGAREEN ENGINEERING
 * Website: 
 * Description: Contains the LCD port configurations, CMD list, function prototypes

The libraries have been tested on ALGAREEN DEVELOPMENT  AVR development boards (PADAA). We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Errors and omissions should be reported to algareen.eng@gmail.com
***************************************************************************************************/



/***************************************************************************************************
                             Revision History
*****************************************************************************************************
1.0: Initial version 
****************************************************************************************************/


#ifndef _LCD_H_
#define _LCD_H_

#include <avr/io.h>		/* where all the Input/Output Registers and its Bits are defined for all AVR micro-controllers*/
#include <util/delay.h> /* which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/


#define LCD_Dir DDRB	/* Define LCD data port direction */
#define LCD_Port PORTB	/* Define LCD data port */
#define RS PB0			/* Define Register Select (data reg./command reg.) signal pin */
#define EN PB1 			/* Define Enable signal pin */



/***************************************************************************************************
                        List of commonly used LCD Commands 
****************************************************************************************************/
#define CMD_LCD_CLEAR                0x01u
#define CMD_LCD_RETURN_HOME          0x02u
#define CMD_DISPLAY_ON_CURSOR_OFF    0x0Cu
#define CMD_DISPLAY_ON_CURSOR_ON     0x0Eu
#define CMD_DISPLAY_ON_CURSOR_BLINK  0x0Fu

#define CMD_FORCE_CURSOR_TO_1ST_LINE  0x80u
#define CMD_FORCE_CURSOR_TO_2ST_LINE  0xC0u

#define CMD_LCD_FOUR_BIT_MODE        0x28u
#define CMD_LCD_EIGHT_BIT_MODE       0x38u


/**************************************************************************************************/



/***************************************************************************************************
                             Function Prototypes
****************************************************************************************************/
void LCD_Init(void);
void LCD_CmdWrite( uint8_t v_lcdCmd_u8);
void LCD_DisplayChar( char v_lcdData_u8);
void LCD_Clear();
void LCD_GoToLine(uint8_t v_lineNumber_u8);
void LCD_GoToNextLine();
void LCD_SetCursor(uint8_t v_lineNumber_u8, uint8_t v_charNumber_u8);
void LCD_DisplayString(const char *ptr_stringPointer_u8);
void LCD_ScrollMessage(uint8_t v_lineNumber_u8, char *ptr_msgPointer_u8);
void LCD_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8);
void LCD_DisplayFloatNumber(double v_floatNum_f32);
void LCD_Printf(const char *argList, ...);

/**************************************************************************************************/

#endif



/***************************************************************************************************
                                   2x16 LCD internal structure
****************************************************************************************************
    
            |<--------------------16 chars on Each Line-------------------->|
           ____________________________________________________________________    
          |\                                                                  /|
          | \ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___/ |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line0 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line1 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
          | /                                                                \ |
          |/__________________________________________________________________\|
                        | D7 D6 D5 D4 D3 D2 D1 D0 |     EN   RW   RS          
                        |<------Lcd Data Bus----->|    Lcd control Lines
                        |                          |          
***************************************************************************************************/                                   







/***************************************************************************************************
                            local function prototypes
***************************************************************************************************/
void LCD_Init(void);
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_String (char *str)	;
void LCD_String_xy (char row, char pos, char *str);

/**************************************************************************************************/



/**************************************************************************************************
void LCD_Init()
***************************************************************************************************
 * Function name: LCD_Init()
 * I/P Arguments: none
 * Return value : none

 * description  :This function is used to initialize the lcd for 4bit mode.
                  
**************************************************************************************************/
void LCD_Init(void)
{

	LCD_Dir = 0xFF;							/* Make LCD command port direction as o/p */
	LCD_Port &=~(1<<EN);					/* Make LCD Enable = 0 */
	
	_delay_ms(20);							/* LCD Power ON delay always >15ms */

	LCD_Command(0x33);
	LCD_Command(0x32);		    			/* send for 4 bit initialization of LCD  */
	LCD_Command(CMD_LCD_FOUR_BIT_MODE);     /* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
	LCD_Command(CMD_DISPLAY_ON_CURSOR_ON);  /* Display on cursor on*/
	LCD_Command(CMD_LCD_CLEAR);             /* Clear display screen*/
	
	_delay_ms(2);
	
	LCD_Command(0x06);              		/* Increment cursor (shift cursor to right)*/
	LCD_Command (0x80);						/* Cursor 1st row 0th position */

}

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);				/* RS=0, command reg. */
	LCD_Port |= (1<<EN);				/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);				/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_String (char *str)				/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);		/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);		/* Command of first row and required position<16 */
	LCD_String(str);					/* Call LCD string function */
}




/***************************************************************************************************
                         void LCD_Clear()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function clears the LCD and moves the cursor to beginning of first line
****************************************************************************************************/
void LCD_Clear()
{
    LCD_Command(CMD_LCD_CLEAR);    // Clear the LCD and go to First line First Position
    _delay_ms(2);
	LCD_Command(CMD_FORCE_CURSOR_TO_1ST_LINE);
}






