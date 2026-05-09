/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include <string.h>
#include <stdio.h>
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
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */
/* Define GPS/NMEA data as constant in Flash */
/* Define GPS/NMEA sentences as const arrays in Flash */
static const uint8_t gpsSentence1[] = {
  0x24,0x47,0x50,0x47,0x53,0x56,0x2C,0x31,0x2C,0x31,0x2C,0x30,0x33,0x2C,0x30,0x35,0x2C,0x2C,0x2C,0x32,0x35,0x2C,
  0x32,0x31,0x2C,0x2C,0x2C,0x32,0x30,0x2C,0x31,0x33,0x2C,0x2C,0x2C,0x31,0x36,0x2A,0x37,0x43,0x0D,0x0A
};
static const uint8_t gpsSentence2[] = {
  0x24,0x47,0x50,0x52,0x4D,0x43,0x2C,0x30,0x37,0x31,0x37,0x35,0x39,0x2E,0x37,0x35,0x35,0x2C,0x41,0x2C,0x33,0x33,
  0x33,0x36,0x2E,0x39,0x38,0x33,0x2C,0x4E,0x2C,0x30,0x37,0x33,0x30,0x35,0x2E,0x39,0x38,0x33,0x2C,0x45,0x2C,0x30,
  0x2E,0x30,0x30,0x2C,0x30,0x2E,0x30,0x30,0x2C,0x30,0x38,0x30,0x31,0x38,0x30,0x2C,0x2C,0x2C,0x4E,0x2A,0x34,0x42,
  0x0D,0x0A
};
static const uint8_t gpsSentence3[] = {
  0x24,0x47,0x50,0x56,0x54,0x47,0x2C,0x30,0x2E,0x30,0x30,0x2C,0x54,0x2C,0x2C,0x4D,0x2C,0x30,0x2E,0x30,0x30,0x2C,
  0x4E,0x2C,0x30,0x2E,0x30,0x30,0x2C,0x4B,0x2C,0x4E,0x2A,0x33,0x32,0x0D,0x0A
};
static const uint8_t gpsSentence4[] = {
  0x24,0x47,0x50,0x47,0x47,0x41,0x2C,0x30,0x37,0x31,0x38,0x30,0x30,0x2E,0x37,0x35,0x35,0x2C,0x33,0x33,0x33,0x36,
  0x2E,0x39,0x38,0x33,0x2C,0x4E,0x2C,0x30,0x37,0x33,0x30,0x35,0x2E,0x39,0x38,0x33,0x2C,0x45,0x2C,0x31,0x2C,0x30,
  0x38,0x2C,0x30,0x2E,0x39,0x2C,0x35,0x34,0x30,0x2E,0x30,0x2C,0x4D,0x2C,0x2C,0x4D,0x2C,0x2C,0x2A,0x35,0x41,0x0D,
  0x0A
};
static const uint8_t gpsSentence5[] = {
  0x24,0x47,0x50,0x47,0x53,0x41,0x2C,0x41,0x2C,0x33,0x2C,0x30,0x35,0x2C,0x31,0x33,0x2C,0x32,0x31,0x2C,0x2C,0x2C,
  0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x31,0x2E,0x38,0x2C,0x30,0x2E,0x39,0x2C,0x31,0x2E,0x35,0x2A,0x33,0x33,0x0D,
  0x0A
};

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
	char msg[100];
	uint32_t adcVal[3];

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
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  // Set this pin High//
	 	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10, GPIO_PIN_SET);
	  // Configure ADC channel for A0 (PA0)
	     ADC_ChannelConfTypeDef sConfig = {0};
	     sConfig.Channel = ADC_CHANNEL_0;
	     sConfig.Rank = 1;
	     sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	     HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	     HAL_ADC_Start(&hadc1);
	     HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	     adcVal[0] = HAL_ADC_GetValue(&hadc1);
	     HAL_ADC_Stop(&hadc1);

	     // Configure ADC channel for A1 (PA1)
	     sConfig.Channel = ADC_CHANNEL_1;
	     HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	     HAL_ADC_Start(&hadc1);
	     HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	     adcVal[1] = HAL_ADC_GetValue(&hadc1);
	     HAL_ADC_Stop(&hadc1);

	     // Configure ADC channel for A2 (PA4)
	     sConfig.Channel = ADC_CHANNEL_4;
	     HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	     HAL_ADC_Start(&hadc1);
	     HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	     adcVal[2] = HAL_ADC_GetValue(&hadc1);
	     HAL_ADC_Stop(&hadc1);
	     // Reset GPIO pin to low//
	     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10, GPIO_PIN_RESET);
	     // Send values over UART
	     sprintf(msg, "X-axis : %lu , Y-axis : %lu , Z-axis : %lu\r\n",
	             adcVal[0], adcVal[1], adcVal[2]);
	     HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	     HAL_Delay(50); // sample every 500ms
		 ////////////////////////////////////
	     // Send GPS sentences one by one
	     HAL_UART_Transmit(&huart2, gpsSentence1, sizeof(gpsSentence1), HAL_MAX_DELAY);
	     HAL_UART_Transmit(&huart2, gpsSentence2, sizeof(gpsSentence2), HAL_MAX_DELAY);
	     HAL_UART_Transmit(&huart2, gpsSentence3, sizeof(gpsSentence3), HAL_MAX_DELAY);
	     HAL_UART_Transmit(&huart2, gpsSentence4, sizeof(gpsSentence4), HAL_MAX_DELAY);
	     HAL_UART_Transmit(&huart2, gpsSentence5, sizeof(gpsSentence5), HAL_MAX_DELAY);

         HAL_Delay(500); // sample every 500ms

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA10 */
    GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
