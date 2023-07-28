/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------

The code includes the necessary header files: "main.h" and "string.h". "main.h"
likely contains the hardware configuration and function prototypes, while "string.h" 
provides string manipulation functions.

*/
#include "main.h"
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*  
This buffer is likely intended to store received data from the GSM module over UART.
A character array cBuff is defined with the string "AT\r\n". This buffer seems to be used 
to send the AT command to the GSM module.
*/
char rcvBuff[512];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t cBuff[10] = "AT\r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	
	/*
The main function is the entry point of the application.
It starts with hardware initialization using HAL (Hardware Abstraction Layer) functions:
HAL_Init(), SystemClock_Config(), MX_GPIO_Init(), and MX_USART2_UART_Init().
The GsmUartSendData() function is called with cBuff and a length of 4. 
This will send the "AT\r\n" command to the GSM module.
The program then enters an infinite loop (while (1)) where it repeatedly sends the "AT\r\n" 
command to the GSM module every 2 seconds.
	*/
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	/*
	
	The SystemClock_Config() function configures the system clock source and its frequency
	using the HSI (High-Speed Internal) oscillator and PLL (Phase-Locked Loop).
	
	*/
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	/*
	
The MX_USART2_UART_Init() function initializes the USART2 peripheral for UART communication.
It sets the UART communication parameters such as baud rate, word length, stop bits, and parity.
It also enables the UART receive interrupt.
	
	*/
	
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */
	/* 
	The code declares a private function GsmUartSendData() without providing its definition.
	This function is likely meant to send data over UART to the GSM module.
	*/
	GsmUartSendData(cBuff, 4);
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		GsmUartSendData(cBuff, 4);
		HAL_Delay(2000);
		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

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
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */
	__HAL_UNLOCK(&huart2);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	/* USER CODE END USART2_Init 2 */


/*

This function is used to initialize the USART2 peripheral for UART communication 
on the STM32 microcontroller.


huart2.Instance = USART2;
This line sets the Instance member of the huart2 structure to USART2, which indicates 
that we are configuring the USART2 peripheral.

UART Configuration:
The following lines configure various parameters of the UART communication on USART2:
huart2.Init.BaudRate = 115200;: Sets the baud rate to 115200 bps.
huart2.Init.WordLength = UART_WORDLENGTH_8B;: Sets the data word length to 8 bits.
huart2.Init.StopBits = UART_STOPBITS_1;: Sets the number of stop bits to 1.
huart2.Init.Parity = UART_PARITY_NONE;: Disables parity checking (no parity bit).
huart2.Init.Mode = UART_MODE_TX_RX;: Enables both transmission and reception (TX and RX).
huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;: Disables hardware flow control.
huart2.Init.OverSampling = UART_OVERSAMPLING_16;: Sets the UART oversampling to 16x.
huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;: Disables one-bit sampling.

huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
This line initializes the advanced UART features of USART2. In this case, it is set 
to UART_ADVFEATURE_NO_INIT, meaning that advanced features are not enabled.

if (HAL_UART_Init(&huart2) != HAL_OK) { Error_Handler(); }
This line calls the HAL function HAL_UART_Init() to initialize the UART communication 
using the configuration provided in the huart2 structure.
If the initialization is not successful (returns HAL_OK), the function Error_Handler() 
is called, indicating that there is an error in the UART initialization.


__HAL_UNLOCK(&huart2);
This line unlocks the UART handle huart2, allowing other functions to access and use it.

__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
This line enables the UART receive interrupt (UART_IT_RXNE) for USART2.
This means that the microcontroller will generate an interrupt whenever data is received and the receive buffer is not empty.

*/
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/*
	
This function is called in case of an error occurrence.
The code provided here simply disables interrupts and enters an infinite loop, 
effectively stopping the program.
	
	*/
	
	/* 6USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

/* USER CODE BEGIN 1 */
/* USER CODE BEGIN 1 */

/*

static gsmUartSendRet_et TxAck = GSM_SEND_FAILURE;
This line declares a static variable TxAck of type gsmUartSendRet_et, which is an enumerated type 
(probably an enum) representing the status of the UART transmission. 
It initializes TxAck with the value GSM_SEND_FAILURE.

if (HAL_UART_Transmit(&huart2, (uint8_t*) sendData, sendLen, GSM_UART_SEND_TIMEOUT) == HAL_OK)
This line calls the HAL function HAL_UART_Transmit() to send data over UART.
The function takes the following arguments:

&huart2: A pointer to the UART handle (UART2) that is already initialized.

(uint8_t*) sendData: A cast of the sendData pointer to a uint8_t*, as the HAL function expects a uint8_t*.

sendLen: The number of bytes to be sent from the sendData buffer.

GSM_UART_SEND_TIMEOUT: A timeout value (probably defined elsewhere) for the UART transmission.

The HAL_UART_Transmit() function returns HAL_OK if the transmission is successful, otherwise,
it returns an error code.

{ TxAck = GSM_SEND_SUCCESS; }
If the UART transmission is successful (i.e., HAL_OK is returned), the code inside the if block 
will be executed. In this case, the variable TxAck is set to GSM_SEND_SUCCESS, indicating that the 
UART transmission was successful.

return TxAck;
The function returns the value of TxAck, which will be either GSM_SEND_SUCCESS or 
GSM_SEND_FAILURE, depending on the success of the UART transmission.

*/


gsmUartSendRet_et GsmUartSendData(uint8_t *sendData, uint16_t sendLen) {
	static gsmUartSendRet_et TxAck = GSM_SEND_FAILURE;

	if (HAL_UART_Transmit(&huart2, (uint8_t*) sendData, sendLen,
			GSM_UART_SEND_TIMEOUT) == HAL_OK) {
		TxAck = GSM_SEND_SUCCESS;
	}
	return TxAck;
}
/* USER CODE END 1 */
char cByte = 0;
uint16_t len =0;

/*

This is the USART2 interrupt handler function.
When data is received over UART, the interrupt is triggered, and this function is called.
It reads the received data (cByte) from the USART2 RDR register and likely stores it in the rcvBuff array.
The function also clears various UART flags related to overrun, parity, framing, and noise errors.

*/

void USART2_IRQHandler(void) {
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_RXNE) != RESET) {
		cByte = USART2->RDR;
//		strncpy(rcvBuff[len], cByte, 1);
	//	len++;
	}
	if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE) != RESET) {
		__HAL_UART_CLEAR_OREFLAG(&huart2);
	}
	if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_PE) != RESET) {
		__HAL_UART_CLEAR_PEFLAG(&huart2);
	}
	if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_FE) != RESET) {
		__HAL_UART_CLEAR_FEFLAG(&huart2);
	}
	if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_NE) != RESET) {
		__HAL_UART_CLEAR_NEFLAG(&huart2);
	}

	/* USER CODE BEGIN USART3_IRQn 0 */

	/* USER CODE END USART3_IRQn 0 */

	/* USER CODE BEGIN USART3_IRQn 1 */

	/* USER CODE END USART3_IRQn 1 */
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
  
  /*
  
  This function is a callback called when an assertion fails, but it is disabled in the provided code.
  
  */
  
}
#endif /* USE_FULL_ASSERT */

