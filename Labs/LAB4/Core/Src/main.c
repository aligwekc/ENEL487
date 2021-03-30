
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

uint8_t cliBufferTx[240];
uint8_t cliBufferRx[20];
uint8_t test[20];
uint8_t word[20];
uint8_t enter[2];
uint8_t next = '>';
char leds[] = "leds";
char query[] = "query";
char help[] = "help";
char timer[] = "timer";


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t count = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	_Bool status = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  uint16_t timecount;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  strcpy((char*)cliBufferTx, "Type 'leds' to turn on/off LED, Type 'query' for state of LED, Type 'timer' for timing test code, 'help' for help\r\n>");
  HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);
  memset(cliBufferTx, 0, sizeof(cliBufferTx));
  HAL_TIM_Base_Start(&htim4);
  int i = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if((HAL_UART_Receive( &huart3, cliBufferRx, 1, 1000) == HAL_OK))
	 	  {

		  	  //char echo = (char*) cliBufferRx[0];
		  	 HAL_UART_Transmit ( &huart3, cliBufferRx, 1, 1000);

		  	 if((strcmp((char*)cliBufferRx[0], '\r')) != 0)
		  	 {
		  		 cliBufferTx[i] = cliBufferRx[0];
		  		 i++;
		  	 }

	 		 if((strcmp((char*)cliBufferRx[0], '\r')) == 0)
	 		 {
	 			//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	 			enter[0] = '\r';
	 			enter[1] = '\n';
	 			enter[2] = '>';
	 			HAL_UART_Transmit ( &huart3, enter, 3, 1000);

	 			 i = 0;
				 strcpy((char*)test, (char*)cliBufferTx);

				  if((strcmp((char*)test, (char*)leds)) == 0)
				  {
					  if(status == 0)
					  {
						  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
						  HAL_UART_Transmit ( &huart3, "Leds on\r\n>", 12, 1000);
						  status = 1;
						  }
					  else
					  {
						  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
						  HAL_UART_Transmit ( &huart3, "Leds off\r\n>", 12, 1000);
						  status = 0;

					  }

				  }
				  else if ((strcmp((char*)test, (char*)query)) == 0)
				  {
					  if(status == 0)
					  {
						  HAL_UART_Transmit ( &huart3, "Led is turned off\r\n>", 20, 1000);
					  }
					  else
					  {
						  HAL_UART_Transmit ( &huart3, "Led is turned on\r\n>", 20, 1000);
					  }


				  }
				  else if ((strcmp((char*)test, (char*)help)) == 0)
				  {
					  strcpy((char*)cliBufferTx, "Type 'leds' to turn on/off LED, Type 'query' for state of LED, Type 'timer' for timing test code, 'help' for help\r\n"
							  "Make sure all small caps, The user can only write/read four "
							  "letters at a time make sure thier correctly spelled.\r\n>");
					  HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

				  }
				  else if ((strcmp((char*)test, (char*)timer)) == 0)
				  {
					  averageTimeTester();
				  }
				  else
				  {
					  strcpy((char*)cliBufferTx, "Wrong word, type 'help' \r\n>");
					  HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);
				  }

				  memset(cliBufferTx, 0, sizeof(cliBufferTx));


			  }
	 	  }



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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 0;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void averageTimeTester()
{

	int a = 0;
	int16_t add32Start, add32Stop;
	int32_t add32 = 0;
	int16_t add64Start, add64Stop;
	int32_t add64 = 0;
	int16_t mult32Start, mult32Stop;
	int32_t mult32 = 0;
	int16_t mult64Start, mult64Stop;
	int32_t mult64 = 0;
	int16_t div32Start, div32Stop;
	int32_t div32 = 0;
	int16_t div64Start, div64Stop;
	int32_t div64 = 0;
	int16_t struct8Start, struct8Stop;
	int32_t struct8 = 0;
	int16_t struct128Start, struct128Stop;
	int32_t struct128 = 0;
	int16_t struct1024Start, struct1024Stop;
	int32_t struct1024 = 0;

	for(int i = 0; i < 100; i++)
	{
		int32_t z = srand(time(0));
		int32_t v = srand(time(0));

		add32Start = start_time();
		a = add_32(z, v);
		add32Stop = stop_time(add32Start);
		add32 = add32 + add32Stop;

		add64Start = start_time();
		a = add_64(z, v);
		add64Stop = stop_time(add64Start);
		add64 = add64 + add64Stop;

		mult32Start = start_time();
		a = multiply_32(z, v);
		mult32Stop = stop_time(mult32Start);
		mult32 = mult32 + mult32Stop;

		mult64Start = start_time();
		a = multiply_64(z, v);
		mult64Stop = stop_time(mult64Start);
		mult64 = mult64 + mult64Stop;

		div32Start = start_time();
		a = divide_32(z, v);
		div32Stop = stop_time(div32Start);
		div32 = div32 + div32Stop;

		div64Start = start_time();
		a = divide_64(z, v);
		div64Stop = stop_time(div64Start);
		div64 = div64 + div64Stop;

		struct8Start = start_time();
		structeight_Copy();
		struct8Stop = stop_time(struct8Start);
		struct8 = struct8 + struct8Stop;

		struct128Start = start_time();
		structonetwentyeight_Copy();
		struct128Stop = stop_time(struct128Start);
		struct128 = struct128 + struct128Stop;

		struct1024Start = start_time();
	    structkilo_Copy();
		struct1024Stop = stop_time(struct1024Start);
		struct1024 = struct1024 + struct1024Stop;

	}
	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for Add two random 32-bit integers: %d \r\n>", add32);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for Add two random 64-bit integers: %d \r\n>", add64);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for multiply two random 32-bit integers: %d \r\n>", mult32);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for multiply two random 64-bit integers: %d \r\n>", mult64);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for divide two random 32-bit integers: %d \r\n>", div32);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for divide two random 64-bit integers: %d \r\n>", div64);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for copy an 8-byte struct using the assignment operator: %d \r\n>", struct8);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for copy a 128-byte struct using the assignment operator: %d \r\n>", struct128);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

	memset(cliBufferTx, 0, sizeof(cliBufferTx));
	sprintf(cliBufferTx, "Average timer for copy a 1024-byte struct using the assignment operator: %d \r\n>", struct1024);
	HAL_UART_Transmit ( &huart3, cliBufferTx, strlen((char*) cliBufferTx), 1000);

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
