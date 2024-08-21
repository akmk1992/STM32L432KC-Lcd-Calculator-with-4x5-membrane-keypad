/*
 * keypad.h
 *
 *  Created on: Jul 17, 2024
 *      Author: Arkar
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_


#include "stm32l4xx_hal.h"

extern char keypad[5][4];

// Function to get the pressed key


 char checkFirstRow(void);
 char checkSecondRow(void);
 char checkThirdRow(void);
 char checkFourthRow(void);
 char checkFifthRow(void);
 char detectKeyPressed(void);
 void keyPadInit(void);
 void readColum(void);




#endif /* INC_KEYPAD_H_ */
