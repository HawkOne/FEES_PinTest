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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

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

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void pintoggle(char port , int pin){
	GPIO_TypeDef * PORT__BASE;
	uint16_t pin_number=0;

	switch (port){
		case 'a': PORT__BASE = GPIOA;
		break;
		case 'b': PORT__BASE = GPIOB;
		break;
		case 'c': PORT__BASE = GPIOC;
		break;
		case 'd': PORT__BASE = GPIOD;
		break;
		case 'e': PORT__BASE = GPIOE;
		break;
		default: PORT__BASE = GPIOA;
		break;
		}
	switch (pin){
		case 0: pin_number = 0x0001;
		break;
		case 1: pin_number = 0x0002;
		break;
		case 2: pin_number = 0x0004;
		break;
		case 3: pin_number = 0x0008;
		break;
		case 4: pin_number = 0x0010;
		break;
		case 5: pin_number = 0x0020;
		break;
		case 6: pin_number = 0x0040;
		break;
		case 7: pin_number = 0x0080;
		break;
		case 8: pin_number = 0x0100;
		break;
		case 9: pin_number = 0x0200;
		break;
		case 10: pin_number = 0x0400;
		break;
		case 11: pin_number = 0x0800;
		break;
		case 12: pin_number = 0x1000;
		break;
		case 13: pin_number = 0x2000;
		break;
		case 14: pin_number = 0x4000;
		break;
		case 15: pin_number = 0x8000;
		break;
	}
	HAL_GPIO_WritePin(PORT__BASE, pin_number, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(PORT__BASE, pin_number, 0);
    HAL_Delay(10);
}

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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_USB_DEVICE_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/* USER CODE END WHILE */

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
    HAL_Delay(10);


         // PWM_ CONTROL
    pintoggle('c',8);  // PWM_HEATER - BATTERY

    pintoggle('a',0);  // PWM_HEATER - BATTERY
    pintoggle('a',1);  // PWM_HEATER - BATTERY
    pintoggle('a',2);  // PWM_HEATER - BATTERY

         // GPIO DI DIREZIONE
    pintoggle('e',7);	// Dir_X
    pintoggle('e',8);	// Dir_Y
    pintoggle('e',9);	// Dir_Z

    	//GPIO DI CONTROLLO
    pintoggle('b',5);	// WATCHDOG
    pintoggle('d',12); 	// TMTC_WD
    pintoggle('e',0);	// ANA_PWR_ON
    pintoggle('e',1);	// RAD_PWR_ON
    pintoggle('e',3);	// SBD_PWR_ON
    pintoggle('e',2);	// GPS_PWR_ON
    pintoggle('e',6);	// RSBY_PWR_ON
    pintoggle('b',0);	// RSBY_KEEP_EN

         // GPIO DI DIREZIONE
    pintoggle('b',1);	// EX_GPIO1
    pintoggle('b',12);	// EX_GPIO2
    pintoggle('a',3);	// EX_GPIO3
    pintoggle('a',10);	// EX_GPIO4


         //CS_SPI_SENSORI
    pintoggle('e',5);  	// CS_NAND
    pintoggle('e',4);  	// CS_LORA
    pintoggle('a',4);	// CS_RADFET
    pintoggle('e',11);	// EN_ADC1
    pintoggle('e',13);	// EN_ADC2
    pintoggle('e',12);	// EN_ADC3
    pintoggle('c',9);  	// EXT_SPI_EN
    pintoggle('d',10);	// CS_EEPROM
    pintoggle('d',11);	// CS_FRAM
    pintoggle('c',4);  	// CS_PSD1_AMP
    pintoggle('c',5);   // CS_PSD2_AMP
    pintoggle('e',10);  // CS_GYRO
    pintoggle('d',14);  // CS_GYRO2




    uint8_t BufferPrint1[20]={"UNOOOO 1!\n"};
    uint8_t BufferPrint2[20]={"DOS! 2!\n"};
    uint8_t BufferPrint3[20]={"TREs!  3!\n"};
    uint8_t BufferPrint6[20]={"666 666 666\n"};

    HAL_UART_Transmit(&huart1, BufferPrint1, 20, 100);
    HAL_Delay(10);

    HAL_UART_Transmit(&huart2, BufferPrint2, 20, 100);
    HAL_Delay(10);

   	HAL_UART_Transmit(&huart3, BufferPrint3, 20, 100);
    HAL_Delay(10);

    HAL_UART_Transmit(&huart6, BufferPrint6, 20, 100);
    HAL_Delay(10);



    uint8_t Buffer[10]={ 0x0099, 0x0056, 0x0104,0x4255,0x0045,0x0043,0x0043,0x0043,0x0043,0x0055};

    HAL_I2C_Init(&hi2c1);
    HAL_I2C_Init(&hi2c2);

    HAL_I2C_Master_Transmit(&hi2c1, 0x0123, Buffer, 10, 100);
    HAL_Delay(10);
    HAL_I2C_Master_Transmit(&hi2c2, 0x0123, Buffer, 10, 100);
    HAL_Delay(10);

    HAL_SPI_Init(&hspi1);
    HAL_SPI_Init(&hspi2);
    HAL_SPI_Init(&hspi3);


    HAL_SPI_Transmit(&hspi1, Buffer, 10, 100);
    HAL_Delay(10);
    HAL_SPI_Transmit(&hspi2, Buffer, 10, 100);
    HAL_Delay(10);
    HAL_SPI_Transmit(&hspi3, Buffer, 10, 100);
    HAL_Delay(10);







//    	// Communication busses pins
//         	   	   // UART _ BUS
//    pintoggle('b',6);  // UART_1_TX	GPS
//    pintoggle('b',7);  // UART_1_RX
//
//    pintoggle('d',5);  // UART_2_TX	SBD
//    pintoggle('d',6);  // UART_2_RX
//
//    pintoggle('d',8);  // UART_3_TX	CONSOLE SERIALE
//    pintoggle('d',9);  // UART_3_RX
//
//    pintoggle('c',6);  // UART_6_TX	SDR
//    pintoggle('c',7);  // UART_6_RX
//
//    		// SPI  BUSSES
//    			// SPI_1
//    pintoggle('a',6);  // SPI_1_MISO
//    pintoggle('a',7);  // SPI_1_MOSI
//    pintoggle('a',5);  // SPI_1_SCK
//    			// SPI_2
//    pintoggle('b',14);  // SPI_2_MISO
//    pintoggle('b',15);  // SPI_2_MOSI
//    pintoggle('b',13);  // SPI_2_SCK
//    			// SPI_3
//    pintoggle('c',11);  // SPI_3_MISO
//    pintoggle('c',12);  // SPI_3_MOSI
//    pintoggle('c',10);  // SPI_3_SCK
//
//
//    		// I2C  BUSSES
//    			// I2C_1
//    pintoggle('b',10);  // SCL
//    pintoggle('b',11);  // SDA
//    			// I2C_2
//    pintoggle('b',8);  // SCL2
//    pintoggle('b',9);  // SDA2


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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPS_PWR_ON_Pin|SBD_PWR_ON_Pin|CS_NAND_Pin|CS_LORA_Pin
                          |RSBY_ON_Pin|DIR_COIL_X_Pin|DIR_COIL_Y_Pin|DIR_COIL_Z_Pin
                          |CS_GYRO_Pin|EN_ADC1_Pin|EN_ADC3_Pin|EN_ADC2_Pin
                          |SBD_SER_RI_Pin|SBD_SER_NET_Pin|ANA_PWR_ON_Pin|RAD_PWR_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, UHF_RESET_Pin|RADFET_OWB_Pin|RAD_RESET_Pin|PSD1_SEL0_Pin
                          |PSD2_SEL1_Pin|PSD2_SEL0_Pin|PSD1_AMP_CS_Pin|PSD2_AMP_CS_Pin
                          |EX_SPI_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PSD1_SEL1_GPIO_Port, PSD1_SEL1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EX_GPIO3_Pin|CS_RADFET_Pin|EX_GPIO4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RSBY_KEEP_EN_Pin|EX_GPIO1_Pin|EX_GPIO2_Pin|WATCHDOG_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, CS_EEPROM_Pin|CS_FRAM_Pin|CS_GYROD12_Pin|INT_GYRO_Pin
                          |CS_GYRO2_Pin|INT_GYRO2_Pin|SBD_SER_DCD_Pin|SBD_SER_DSR_Pin
                          |SBD_SER_DTR_Pin|SBD_SER_CTS_Pin|SBD_SER_RTS_Pin|SBD_ON_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GPS_PWR_ON_Pin SBD_PWR_ON_Pin CS_NAND_Pin CS_LORA_Pin
                           RSBY_ON_Pin DIR_COIL_X_Pin DIR_COIL_Y_Pin DIR_COIL_Z_Pin
                           CS_GYRO_Pin EN_ADC1_Pin EN_ADC3_Pin EN_ADC2_Pin
                           SBD_SER_RI_Pin SBD_SER_NET_Pin ANA_PWR_ON_Pin RAD_PWR_ON_Pin */
  GPIO_InitStruct.Pin = GPS_PWR_ON_Pin|SBD_PWR_ON_Pin|CS_NAND_Pin|CS_LORA_Pin
                          |RSBY_ON_Pin|DIR_COIL_X_Pin|DIR_COIL_Y_Pin|DIR_COIL_Z_Pin
                          |CS_GYRO_Pin|EN_ADC1_Pin|EN_ADC3_Pin|EN_ADC2_Pin
                          |SBD_SER_RI_Pin|SBD_SER_NET_Pin|ANA_PWR_ON_Pin|RAD_PWR_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : UHF_RESET_Pin RADFET_OWB_Pin RAD_RESET_Pin PSD1_SEL1_Pin
                           PSD1_SEL0_Pin PSD2_SEL1_Pin PSD2_SEL0_Pin PSD1_AMP_CS_Pin
                           PSD2_AMP_CS_Pin EX_SPI_EN_Pin */
  GPIO_InitStruct.Pin = UHF_RESET_Pin|RADFET_OWB_Pin|RAD_RESET_Pin|PSD1_SEL1_Pin
                          |PSD1_SEL0_Pin|PSD2_SEL1_Pin|PSD2_SEL0_Pin|PSD1_AMP_CS_Pin
                          |PSD2_AMP_CS_Pin|EX_SPI_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PWM_X_COIL_Pin PWM_Y_COIL_Pin PWM_Z_COIL_Pin */
  GPIO_InitStruct.Pin = PWM_X_COIL_Pin|PWM_Y_COIL_Pin|PWM_Z_COIL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EX_GPIO3_Pin CS_RADFET_Pin EX_GPIO4_Pin */
  GPIO_InitStruct.Pin = EX_GPIO3_Pin|CS_RADFET_Pin|EX_GPIO4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RSBY_KEEP_EN_Pin EX_GPIO1_Pin EX_GPIO2_Pin WATCHDOG_Pin */
  GPIO_InitStruct.Pin = RSBY_KEEP_EN_Pin|EX_GPIO1_Pin|EX_GPIO2_Pin|WATCHDOG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_EEPROM_Pin CS_FRAM_Pin CS_GYROD12_Pin INT_GYRO_Pin
                           CS_GYRO2_Pin INT_GYRO2_Pin SBD_SER_DCD_Pin SBD_SER_DSR_Pin
                           SBD_SER_DTR_Pin SBD_SER_CTS_Pin SBD_SER_RTS_Pin SBD_ON_OFF_Pin */
  GPIO_InitStruct.Pin = CS_EEPROM_Pin|CS_FRAM_Pin|CS_GYROD12_Pin|INT_GYRO_Pin
                          |CS_GYRO2_Pin|INT_GYRO2_Pin|SBD_SER_DCD_Pin|SBD_SER_DSR_Pin
                          |SBD_SER_DTR_Pin|SBD_SER_CTS_Pin|SBD_SER_RTS_Pin|SBD_ON_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PWM_HEATER_Pin */
  GPIO_InitStruct.Pin = PWM_HEATER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(PWM_HEATER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PGOOD_Pin */
  GPIO_InitStruct.Pin = PGOOD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PGOOD_GPIO_Port, &GPIO_InitStruct);

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
