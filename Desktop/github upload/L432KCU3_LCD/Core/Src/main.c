/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * Author :Arkar
  * Description :
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HD44780.h"
#include "keypad.h"
#include "calculator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
 * Function :void show2Strings(char* str1,char* str2)
 * Description : This function display the two strings in two different positions
 * @param : str1, str2
 * Return : None
 * */

void show2Strings(char* str1,char* str2) {
	HD44780_GotoXY(0, 0);
	HD44780_PutStr(str1);
	HD44780_GotoXY(0, 1);
	HD44780_PutStr(str2);
}

void msDelay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a period to guaranty minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)uwTickFreq;
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//static uint8_t count = 0;
	//Dialog1.stringName = {"Hi","How are You?","I'm good" ,"Thank you!","Have a good day",":-)","You too!","See you Soon","See ya :-)","Bye"};

	char *string[8] = {"Hello All","I'm Arkar","I'm working on","a simple LCD","Calculator","Project","Thank you!",":-)"};



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  keyPadInit();


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HD44780_Init(); //initialize LCD Display


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

#if 0
	  uint32_t timestamp = HAL_GetTick();
	  uint16_t rxBuffer[]={0};
	  char message[100]= {'\0'};
	  sprintf(message,"counter value is %x \n\r",timestamp);
	  HAL_UART_Transmit(&huart2, (uint8_t*)message, sizeof(message), 100);
	  HAL_Delay(2000);
	  //HAL_UART_Receive(&huart2, pData, Size, Timeout)
#endif

	  static uint8_t numCount =0;
	  char key;
	  char inputBuffer[16] ={0};
	  char outputBuffer[16] ={0};
	  uint8_t input_index =0;
	  float num1,num2,result;



	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)){

		  //This loop print out the greeting message
			  for (int8_t i=0 ; i<sizeof(string)/sizeof(string[0]) ;i++){

			  	  HAL_GPIO_WritePin(GPIOB/*On-board led port*/, LD3_Pin/*it's PB3*/, GPIO_PIN_SET);
			  	  HD44780_ClrScr(); //Clear LCD screen
			  	  show2Strings(string[i], string[i+1]);

			  	  i++;
			  	  msDelay(1000);
			  	  HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
			  	  HAL_Delay(1000);

			  }

			  HD44780_ClrScr();// clear the greeting screen

			  //This loop for the calculation
			  do {
				  if(numCount ==0){
					  HD44780_PutStr("Num1:");
					  numCount++;
				  }


				  key = detectKeyPressed();//read the keypad input

				  	  if (key !='\0'){
				  		  //check if Enter Key
				  		  if (key == 'E'){
				  			  numCount++;
				  			  num1 =atof(inputBuffer);//convert back char to integer
				  			  memset(inputBuffer,0,sizeof(inputBuffer));//clear the buffer
				  			  input_index =0;
				  			  HD44780_ClrScr();

				  		  }
				  		  //handle the wrong input and press Esc to clear the buffer
				  		  else if(key == 'X'){
				  			HD44780_ClrScr();
				  			memset(inputBuffer,0,sizeof(inputBuffer));
				  			input_index =0;
				  			numCount=0;
				  		  }
				  		  //accept the rest of the key input
				  		  else{
						  	  	HD44780_PutChar(key);
						  	  	inputBuffer[input_index++]=key;
						  		HAL_Delay(30);

				  		  }

				  	  }
				  	  /*This condition store the input in the buffer and
				  	   * change to int type and store in num2
				  	   * */

				  	  if(numCount == 2){

							HD44780_PutStr("Num2:");
							while(1){

								key = detectKeyPressed();
								 if(key !=0 && key !='E' && key !='X')
								  {
									  HD44780_PutChar(key);
									  inputBuffer[input_index++]=key;
									  HAL_Delay(30);
								  }
								 /*handle to clear the buffer if press Esc button
								  * in case if we press the wrong input */
							  	else if(key == 'X'){
							  			HD44780_ClrScr();
							  			memset(inputBuffer,0,sizeof(inputBuffer));
							  			input_index =0;
							  			break;
							  		  }

								 //check if Enter Key and register the number to num2
								 else if (key == 'E'){
									 numCount++;
						  			  num2 =atof(inputBuffer);
						  			  memset(inputBuffer,0,sizeof(inputBuffer));
						  			  input_index =0;
						  			  HD44780_ClrScr();
									  break;
								 }
							}


						 }

				  	  /*This condition take the operator character and do the calculation
				  	   * of the two inputs And print on LCD and allows user to clear the screen
				  	   * if the input is wrong
				  	   * */
				  	  if(numCount ==3){
							HD44780_PutStr("Operator:");
							while(1){

								key = detectKeyPressed();
								 if(key !=0 && key !='E' && key !='X')
								  {
									if (key=='+' || key=='-' || key== '*' || key =='/' || key=='^'){
									HD44780_PutChar(key);
									result= calculate(num1, num2,key);
									snprintf(outputBuffer,sizeof(outputBuffer)," %0.3f",result);
									HD44780_GotoXY(0,1);
									HD44780_PutStr(outputBuffer);
									HAL_Delay(3000);
									//HD44780_ClrScr();
									memset(outputBuffer,0,sizeof(outputBuffer));
									numCount =0;

									//break;
									}



									/*Error handling for operator input :
									 * For operator inputs other than +,-,*,/,^ keys are pressed ,
									 * it display the error
									 * message*/

									else{
										HD44780_ClrScr();
										result= calculate(num1, num2,key);
										break;
									}


								  }

								 //clear the screen after display the result
								 else if(key == 'X'){
										HD44780_ClrScr();
										break;

									}


							}


				  	  }

			  }while(1); //do while(1) loop end here.


	  }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|ROW1_OUTPUT_Pin|ROW2_OUTPUT_Pin|ROW3_OUTPUT_Pin
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|ROW4_OUPUT_Pin|ROW5_OUTPUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 ROW1_OUTPUT_Pin ROW2_OUTPUT_Pin ROW3_OUTPUT_Pin
                           PA7 PA8 PA9 PA10
                           PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|ROW1_OUTPUT_Pin|ROW2_OUTPUT_Pin|ROW3_OUTPUT_Pin
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : COL1_INPUT_Pin COL4_INPUT_Pin COL3_INPUT_Pin COL2_INPUT_Pin */
  GPIO_InitStruct.Pin = COL1_INPUT_Pin|COL4_INPUT_Pin|COL3_INPUT_Pin|COL2_INPUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin ROW4_OUPUT_Pin ROW5_OUTPUT_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|ROW4_OUPUT_Pin|ROW5_OUTPUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
