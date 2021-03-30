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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* Definitions for defaultTask
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};*/
/* Definitions for cliTask */
osThreadId_t cliTaskHandle;
const osThreadAttr_t cliTask_attributes = {
  .name = "cliTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for statusUpdateTask */
osThreadId_t statusUpdateTaskHandle;
const osThreadAttr_t statusUpdateTask_attributes = {
  .name = "statusUpdateTask",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for stateControllerTask */
osThreadId_t stateControllerTaskHandle;
const osThreadAttr_t stateControllerTask_attributes = {
  .name = "stateControllerTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for CLITaskQueue */
osMessageQueueId_t CLITaskQueueHandle;
const osMessageQueueAttr_t CLITaskQueue_attributes = {
  .name = "CLITaskQueue"
};
/* Definitions for statusQueueUpdate */
osMessageQueueId_t statusQueueUpdateHandle;
const osMessageQueueAttr_t statusQueueUpdate_attributes = {
  .name = "statusQueueUpdate"
};
/* Definitions for myTimer01 */
osTimerId_t myTimer01Handle;
const osTimerAttr_t myTimer01_attributes = {
  .name = "myTimer01"
};
/* USER CODE BEGIN PV */
const static char* PROMPT = "cmd> ";
#define CLEAR "\x1b[2J"
#define RC(r,c) "\x1b[" #r ";" #c "f"
#define ROLL_TO_BOTTOM(r) "\x1b[" #r ";r"
#define SAVE_CURSOR "\x1b[s"
#define RESTORE_CURSOR "\x1b[u"
#define MAX_USER_INPUT  100
#define forward "\x1b[1C"

uint8_t cliBufferTX[MAX_USER_INPUT];
uint8_t cliRXChar;
uint8_t cliBufferRX[MAX_USER_INPUT];
bool linecomplete = false;
int counter = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
void cliTask_begin(void *argument);
void update_statusTask(void *argument);
void controller_stateTask(void *argument);
void Callback01(void *argument);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
    //Clear the screen
        strcpy ( cliBufferTX, "\x1b[2J" );
        printStringBlocking("\x1b[2J");
        printStringBlocking(CLEAR);   // clears the screen
        HAL_Delay(500);
        //Prints the welcome message
        //welcomeMessage();
        HAL_Delay(2000);

        //Clear the screen
        printStringBlocking(CLEAR);   // clear entire screen

        printStringBlocking(RC(5,1)); // cursor to row number, column number
        printStringBlocking(ROLL_TO_BOTTOM(5)); // set scrolling region
                                                     // to row number->bottom
        printStringBlocking(RC(5,1)); // cursor to row number, column number (must call this
           	                                 // again, because the set scroll
        printStringBlocking(PROMPT);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  CLITaskQueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &CLITaskQueue_attributes);
  statusQueueUpdateHandle = osMessageQueueNew (1, sizeof(uint16_t), &statusQueueUpdate_attributes);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  /* defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);*/
  /* creation of cliTask */
   cliTaskHandle = osThreadNew(cliTask_begin, NULL, &cliTask_attributes);

   /* creation of statusUpdateTask */
   statusUpdateTaskHandle = osThreadNew(update_statusTask, NULL, &statusUpdateTask_attributes);

   /* creation of stateControllerTask */
   stateControllerTaskHandle = osThreadNew(controller_stateTask, NULL, &stateControllerTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

    /*Configure GPIO pins : PA6 PA7 PA8 PA9 */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void printString (const char* message)
{
    int i=0;
    HAL_StatusTypeDef	status;

    //Have to wait for the last transmission to go.
    while(huart3.gState == HAL_UART_STATE_BUSY_TX){}

	for (const char* p = message; *p; ++p) {
    	cliBufferTX[i] =  *p;
    	i++;
    }
	status = HAL_UART_Transmit_IT(&huart3, cliBufferTX, i);
	if (status!= HAL_OK)
	{
		Error_Handler();
	}

}

void printStringBlocking (const char* message)
{
    int i=0;
    HAL_StatusTypeDef	status;

    //wait for the last transmission to go.
    while(huart3.gState == HAL_UART_STATE_BUSY_TX){}

	for (const char* p = message; *p; ++p) {
    	cliBufferTX[i] =  *p;
    	i++;
    }
	status = HAL_UART_Transmit(&huart3, cliBufferTX, i, 1000);
	if (status!= HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * Send a byte
 */
void sendByte (char message_Character)
{
    while(huart3.gState == HAL_UART_STATE_BUSY_TX){}
	HAL_UART_Transmit(&huart3, &message_Character, 1, 1000);

}

_Bool line(cliBufferRX, cliRXChar)
{

	  int i = 0;
	  int num = 1;
	  char enterChar = '\r';
	  char test;
	  _Bool correct = false;


	  sendByte(cliRXChar);

	  test = (char)cliRXChar;
	  if(test != enterChar)
	  {

		  correct = false;
	  }

	  if(test == enterChar)
	  {
		  /*

		  */
		  correct = true;
	  }

	 return correct;

}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_cliTask_begin */
/**
  * @brief  Function implementing the cliTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_cliTask_begin */
void cliTask_begin(void *argument)
{
  /* USER CODE cliTask_begin start */
	uint16_t cli_message =1000;
	uint16_t value = 0;
	char failsafemode[] = "mode fsm";
	char staticcyclemode[] = "mode scm";
	char atmmode[] = "atm";
	char help[] = "help";
	char space = ' ';
	uint8_t accelerating_factor[10];

  /* Infinite loop */
  for(;;)
  {
	  //this code block begins the data receiving process
	 if ((HAL_UART_Receive ( &huart3, &cliRXChar, 1, 10) == HAL_OK))
	 {

		//Check if the line is complete
		linecomplete =  line(cliBufferRX, cliRXChar);
		if(!line)
		{
			cliBufferRX[strlen((char*) cliBufferRX)] = cliRXChar;
		}

		if(line)
		{

			if((strcmp((char*)cliBufferRX, (char*)failsafemode)) == 0)
			{
				cli_message = 12345;
			}
			else if((strcmp((char*)cliBufferRX, (char*)staticcyclemode)) == 0)
			{
				cli_message = 12121;
			}
			else if((strcmp((char*)cliBufferRX, (char*)help)) == 0)
			{
				cli_message = 4444;
			}
			else if(cliBufferRX[0] == 'a' && cliBufferRX[1] == 't' && cliBufferRX[2] == 'm' )
			{
				if((char)cliBufferRX[3] == space)
				{
					for(int j = 0; j < (strlen((char*) cliBufferRX) - 4); j++)
					{
						accelerating_factor[j] =  cliBufferRX[j + 4];
					}

					value = atoi((char*)accelerating_factor);
					if((value <= 100) && (value > 0))
					{
						cli_message = value;
					}
					else
					{
						cli_message = 1010;
					}
				}
				else if((char)cliBufferRX[3] != space)
				{
					cli_message = 1010;
				}

			}
			else
			{
				cli_message = cli_message;
			}

			memset(cliBufferRX, 0, sizeof(cliBufferRX));
			memset(accelerating_factor, 0, sizeof(accelerating_factor));
			printStringBlocking("\r\n");
			printStringBlocking(PROMPT);

			//Send a message to the controller.


			if(osMessageQueuePut(CLITaskQueueHandle, &cli_message, 1U, 0U)!= osOK)
			{
			   Error_Handler();
			}
		 }
	 }
	 osDelay(50);
  }
  /* USER CODE END cliTask_begin */
}

void update_statusTask(void *argument)
{
  /* USER CODE BEGIN update_statusTask */

	uint16_t status_message;
	  uint16_t period;
	  osStatus_t status;

  /* Infinite loop */
  for(;;)
  {
	  static char display_string[50];
	  status = osMessageQueueGet(statusUpdateTaskHandle, &status_message, NULL, 0U );
	  if(status == osOK)
	  {
		  period = status_message;
	  }

	  printStringBlocking(SAVE_CURSOR);
	  printStringBlocking(RC(1,1));

	  RC(1,1);
	  if((period > 100) && (period < 0) && (period != 12121) && (period != 4444) && (period != 12345))
	  {
		  strcpy ( display_string, "invalid command! \r\n" );
	  }
	  else if((period == 4444))
	  {
		  strcpy ( display_string, "choose either of the three 'mode fsm', 'mode scm', 'atm x' \r\n" );
	  }
	  else
	  {
		  snprintf(display_string, 50,"period:% 5d \r\n",period);
	  }
	  printStringBlocking(display_string);
	  printStringBlocking(RESTORE_CURSOR);

	  osDelay(50);
  }
  /* USER CODE END update_statusTask */
}

void controller_stateTask(void *argument)
{
  /* USER CODE BEGIN controller_stateTask */
	 	uint16_t cli_message;
	 	uint16_t time_out;
		uint16_t status_message;
		osStatus_t status;
		uint16_t period = 1000;
		_Bool FSM = true;
		_Bool SCM = false;
		osTimerId_t one_shot_id;
		HAL_TIM_Base_Start(&htim2);
		uint16_t time_count;
		uint16_t state = 0;
		uint16_t count = 1000;
		uint16_t state_count = 0;
		uint16_t temp_count = 0;

	if(osMessageQueuePut(statusQueueUpdateHandle, &status_message, 1U, 0U)!= osOK)
	  {
	    Error_Handler();
	  }

  /* Infinite loop */
  for(;;)
  {

		//check for messages but without blocking
		status = osMessageQueueGet(CLITaskQueueHandle, &cli_message, NULL, 0U );
		if(status == osOK)
		{
			//message received
			period = cli_message;
			status_message = cli_message;

			if(osMessageQueuePut(statusQueueUpdateHandle, &status_message, 1U, 0U)!= osOK)
		    {
			  Error_Handler();
			}
			if(cli_message == 12345)
			{
				FSM = true;
				SCM = false;
				state = 0;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
			}
			else if(cli_message == 12121)
			{
				FSM = false;
				SCM = true;
				state_count = 0;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
			}
			else if((period <= 100) && (period > 0))
			{
				count = (1000 / cli_message);
			}

		}
		if(FSM)
		{

			time_count =  __HAL_TIM_GET_COUNTER(&htim2);
			if(!(time_count % 1000))
			{
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
				while(!(__HAL_TIM_GET_COUNTER(&htim2) % count)){}
			}

		}
		if(SCM)
		{
			time_count =  __HAL_TIM_GET_COUNTER(&htim2);
			if(!(time_count % count))
			{
				while(!(__HAL_TIM_GET_COUNTER(&htim2) % count)){}
				state_count++;

				if(state_count == 1)
				{
					state = 0;
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // on primary green
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // on primary walk
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // on secondary red
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET); //  off secondary walk
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); // off secondary yellow
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // off primary yellow
				}
				else if(state_count == 141)
				{
					state = 1;
				}
				else if (state_count == 167)
				{
					state = 0;
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // off primary green
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // off primary walk
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); // on primary yellow
				}
				else if (state_count == 174)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);// on primary red
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);// off primary yellow
				}
				else if (state_count == 186)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//on secondary green
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);//on secondary walk
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);// off secondary Red
				}
				else if(state_count == 226)
				{
					state = 2;
				}
				else if(state_count == 242)
				{
					state = 0;
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);// off secondary green
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//on secondary yellow
				}
				else if(state_count == 249)
				{
					state_count = 0;
				}
				if (state == 1)
				{
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9); //toggle primary walk
				}
				else if (state == 2)
				{
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);// toggle secondary walk on
				}


			}
		}


	    osDelay(50);
  }
  /* USER CODE controller_stateTask END  */
}


void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */


  /* USER CODE END Callback01 */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
