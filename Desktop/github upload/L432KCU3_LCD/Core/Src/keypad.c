/*
 * keypad.c
 *
 *  Created on: Jul 17, 2024
 *  Author: Arkar
 *
 *  Function : char detectKeyPressed(void)
 *  Description This function read the keypad input and display on LCD
 *  Parameters :None
 */



#include <stdio.h>
#include <math.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "debounce.h"



// Define the keypad layout
char keypad[5][4] = {
    {'+', '-', '#', '*'},
    {'1', '2', '3', '^'},
    {'4', '5', '6', '/'},
    {'7', '8', '9', 'X'},
    {'.', '0', '>', 'E'}
};



//#Not in use
//GPIO_TypeDef* COLUMN_PORT[4] = {GPIOB, GPIOA, GPIOB/*GPIOB*/, GPIOB};
//uint16_t COLUMN_PIN[4] = {GPIO_PIN_0, GPIO_PIN_6, GPIO_PIN_6, GPIO_PIN_1}; #not in use

// Column pins (inputs)
char COLUMN_PORT[4] = {'B','A', 'B','B'};
int16_t COLUMN_PIN[4] = {0, 6, 6, 1};



// Row pins (outputs)
GPIO_TypeDef* ROW_PORT[5] = {GPIOA, GPIOA, GPIOA, GPIOB, GPIOB};
uint16_t ROW_PIN[5] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_4, GPIO_PIN_5};



void keyPadInit(void){

	deBounceInit(0,'B',0);
	deBounceInit(6,'A',0);
	deBounceInit(6,'B',0);
	deBounceInit(1,'B',0);
}



/*
 * Function :char checkFirstRow(void)
 * Description : This function detec the first row keys and return the key input
 * @param : None
 * Return : keypad
 * */
char checkFirstRow(void) {
    // Set all rows low
    for (int8_t row = 0; row < 5; row++) {
        HAL_GPIO_WritePin(ROW_PORT[row], ROW_PIN[row], GPIO_PIN_RESET);
    }

    // Set the second row high
    HAL_GPIO_WritePin(ROW_PORT[0], ROW_PIN[0], GPIO_PIN_SET);


    // Check all columns

    int8_t col0=deBounceReadPin(COLUMN_PIN[0],COLUMN_PORT[0], 100);

    int8_t col1=deBounceReadPin(COLUMN_PIN[1],COLUMN_PORT[1], 100);

    int8_t col2=deBounceReadPin(COLUMN_PIN[2],COLUMN_PORT[2], 100);

    int8_t col3=deBounceReadPin(COLUMN_PIN[3],COLUMN_PORT[3], 100);

    // Handle each column independently
    if (col0 == GPIO_PIN_SET) {
        return keypad[0][0];
    }

    if (col1 == GPIO_PIN_SET) {
      return keypad[0][1];
   }

    if (col2 == GPIO_PIN_SET) {
    	 return keypad[0][2];
    }

    if (col3 == GPIO_PIN_SET) {
    	 return keypad[0][3];
    }

    return 0;
}



char checkSecondRow(void) {
    // Set all rows low
    for (int8_t row = 0; row < 5; row++) {
        HAL_GPIO_WritePin(ROW_PORT[row], ROW_PIN[row], GPIO_PIN_RESET);
    }

    // Set the second row high
    HAL_GPIO_WritePin(ROW_PORT[1], ROW_PIN[1], GPIO_PIN_SET);

    int8_t col0=deBounceReadPin(COLUMN_PIN[0],COLUMN_PORT[0], 80);

    int8_t col1=deBounceReadPin(COLUMN_PIN[1],COLUMN_PORT[1], 80);

    int8_t col2=deBounceReadPin(COLUMN_PIN[2],COLUMN_PORT[2], 80);

    int8_t col3=deBounceReadPin(COLUMN_PIN[3],COLUMN_PORT[3], 80);

    // Handle each column independently
    if (col0 == GPIO_PIN_SET) {

        return keypad[1][0];
    }

    if (col1 == GPIO_PIN_SET) {

    	return keypad[1][1];
    }

    if (col2 == GPIO_PIN_SET) {

    	return keypad[1][2];
    }

    if (col3 == GPIO_PIN_SET) {

    	return keypad[1][3];
    }

    return 0;
}



char checkThirdRow(void){


    for ( int8_t row = 0; row < 5; row++) {
        // Set all rows high
           HAL_GPIO_WritePin(ROW_PORT[row], ROW_PIN[row], GPIO_PIN_RESET);

    }


        HAL_GPIO_WritePin(ROW_PORT[2], ROW_PIN[2], GPIO_PIN_SET);

        int8_t col0=deBounceReadPin(COLUMN_PIN[0],COLUMN_PORT[0], 80);


        int8_t col1=deBounceReadPin(COLUMN_PIN[1],COLUMN_PORT[1], 80);


        int8_t col2=deBounceReadPin(COLUMN_PIN[2],COLUMN_PORT[2], 80);


        int8_t col3=deBounceReadPin(COLUMN_PIN[3],COLUMN_PORT[3], 80);

    	if (col0 == GPIO_PIN_SET){

    		return keypad[2][0];
    		}

    	else if ( col1== GPIO_PIN_SET){
    		return keypad[2][1];
    	 }

    	else if (col2 == GPIO_PIN_SET){
    		return keypad[2][2];
    	}

    	else if (col3 == GPIO_PIN_SET){
    		return keypad[2][3];
    	}

    	else{
    		return 0;
    	}


}



char checkFourthRow(void){


    for ( int8_t row = 0; row < 5; row++) {
        // Set all rows high
           HAL_GPIO_WritePin(ROW_PORT[row], ROW_PIN[row], GPIO_PIN_RESET);

    }


        HAL_GPIO_WritePin(ROW_PORT[3], ROW_PIN[3], GPIO_PIN_SET);

        int8_t col0=deBounceReadPin(COLUMN_PIN[0],COLUMN_PORT[0], 80);

        int8_t col1=deBounceReadPin(COLUMN_PIN[1],COLUMN_PORT[1], 80);

        int8_t col2=deBounceReadPin(COLUMN_PIN[2],COLUMN_PORT[2], 80);

        int8_t col3=deBounceReadPin(COLUMN_PIN[3],COLUMN_PORT[3], 80);

    	if (col0 == GPIO_PIN_SET){
    		return keypad[3][0];
    		}

    	else if ( col1== GPIO_PIN_SET){
    		return keypad[3][1];
    	 }

    	else if (col2 == GPIO_PIN_SET){
    		return keypad[3][2];
    	}

    	else if (col3 == GPIO_PIN_SET){
    		return keypad[3][3];
    	}

    	else{
    		return 0;
    	}


}


char checkFifthRow(void){


    for ( int8_t row = 0; row < 5; row++) {
        // Set all rows high
           HAL_GPIO_WritePin(ROW_PORT[row], ROW_PIN[row], GPIO_PIN_RESET);

    }


        HAL_GPIO_WritePin(ROW_PORT[4], ROW_PIN[4], GPIO_PIN_SET);

        int8_t col0=deBounceReadPin(COLUMN_PIN[0],COLUMN_PORT[0], 80);

        int8_t col1=deBounceReadPin(COLUMN_PIN[1],COLUMN_PORT[1], 80);

        int8_t col2=deBounceReadPin(COLUMN_PIN[2],COLUMN_PORT[2], 80);

        int8_t col3=deBounceReadPin(COLUMN_PIN[3],COLUMN_PORT[3], 80);

    	if (col0 == GPIO_PIN_SET){
    		return keypad[4][0];
    		}

    	else if ( col1== GPIO_PIN_SET){
    		return keypad[4][1];
    	 }

    	else if (col2 == GPIO_PIN_SET){
    		return keypad[4][2];
    	}

    	else if (col3 == GPIO_PIN_SET){
    		return keypad[4][3];
    	}

    	else{
    		return 0;
    	}


}





	/*
	 * Function :char detectKeyPressed(void)
	 * Description : This function detect the whole keypad by integrating all rows functions
	 * @param : None
	 * Return : char  key
	 * */
	char detectKeyPressed(void) {
	    char key = 0;

	    // Check the first row
	    key = checkFirstRow();

	    if (key) {
	        return key;
	    }

	    // Check the second row
	    key = checkSecondRow();
	    if (key ) {
	        return key;
	    }

	    // Check the third row
	    key = checkThirdRow();
	    if (key) {
	        return key;
	    }

	    // Check the fourth row
	    key = checkFourthRow();
	    if (key ) {
	        return key;
	    }

	    // Check the fifth row
	    key = checkFifthRow();
	    if (key) {
	        return key;
	    }

	    // Return 0 if no key is pressed
	    return 0;

	}



