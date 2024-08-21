/*
 *
 *
 * calculator.c
 *
 *  Created on: Aug 16, 2024
 *  Author: Arkar
 *  Function : calculate(float num1, float num2, char operator)
 *  Description This function calculate the result of two inputs taken from keypad and it can do the following
 *  arithmetic functions : addition,subtraction, multiplication,division and power
 *  Parameters :float num1, num2 , operator = +,-,*,/,^
 *  @Retval: float , return the result
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HD44780.h"
#include "keypad.h"


float calculate(float num1,float num2,char operator){

	float output =0 ;
	switch (operator){
	case '+' : output =num1+num2 ;break;
	case '-' : output =num1-num2 ;break;
	case '*' : output =num1*num2 ;break;
	case '^' : output =pow(num1,num2);break;
	case '/' :
			if(num2 !=0){
				output =num1/num2 ;
			}
			else {
				HD44780_ClrScr();
				HD44780_PutStr("Input error!");
				HD44780_GotoXY(0,1);
				HAL_Delay(100);
				return UINT32_MAX;


			}

			break;


	default :
			HD44780_PutStr("Operator error!");
			HAL_Delay(100);
			HD44780_ClrScr();
			return UINT32_MAX;
			break;


	}


	return output;
}
