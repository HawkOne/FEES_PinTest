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



//------- COMPILING SETTINGS ----------//

//#define WINDOWS
//#define LINUX

//#define ARDUPILOT
//#define FREERTOS
//#define CHIBIOS

#define BAREMETAL  //ST's HAL LIBRARIES
#define FREERTOS

//#define UNIT_TESTING

//------- ------- ------- ------ ----- //




/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

//FEES RELATED INCLUDES

#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <limits.h>

//#include "1_HardwareAndDrivers.hpp"




/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void Hardware_Watchdog_Refresh(){
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, 1);
    osDelay(100);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, 0);
    osDelay(100);
}
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

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task1 */
osThreadId_t Task1Handle;
uint32_t Task1Buffer[ 128 ];
osStaticThreadDef_t Task1ControlBlock;
const osThreadAttr_t Task1_attributes = {
  .name = "Task1",
  .stack_mem = &Task1Buffer[0],
  .stack_size = sizeof(Task1Buffer),
  .cb_mem = &Task1ControlBlock,
  .cb_size = sizeof(Task1ControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task2 */
osThreadId_t Task2Handle;
uint32_t Task2Buffer[ 128 ];
osStaticThreadDef_t Task2ControlBlock;
const osThreadAttr_t Task2_attributes = {
  .name = "Task2",
  .stack_mem = &Task2Buffer[0],
  .stack_size = sizeof(Task2Buffer),
  .cb_mem = &Task2ControlBlock,
  .cb_size = sizeof(Task2ControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task3 */
osThreadId_t Task3Handle;
uint32_t Task3Buffer[ 128 ];
osStaticThreadDef_t Task3ControlBlock;
const osThreadAttr_t Task3_attributes = {
  .name = "Task3",
  .stack_mem = &Task3Buffer[0],
  .stack_size = sizeof(Task3Buffer),
  .cb_mem = &Task3ControlBlock,
  .cb_size = sizeof(Task3ControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task4 */
osThreadId_t Task4Handle;
uint32_t Task4Buffer[ 128 ];
osStaticThreadDef_t Task4ControlBlock;
const osThreadAttr_t Task4_attributes = {
  .name = "Task4",
  .stack_mem = &Task4Buffer[0],
  .stack_size = sizeof(Task4Buffer),
  .cb_mem = &Task4ControlBlock,
  .cb_size = sizeof(Task4ControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task5 */
osThreadId_t Task5Handle;
uint32_t Task5Buffer[ 128 ];
osStaticThreadDef_t Task5ControlBlock;
const osThreadAttr_t Task5_attributes = {
  .name = "Task5",
  .stack_mem = &Task5Buffer[0],
  .stack_size = sizeof(Task5Buffer),
  .cb_mem = &Task5ControlBlock,
  .cb_size = sizeof(Task5ControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task6 */
osThreadId_t Task6Handle;
uint32_t TaskBuffer[ 128 ];
osStaticThreadDef_t TaskControlBlock;
const osThreadAttr_t Task6_attributes = {
  .name = "Task6",
  .stack_mem = &TaskBuffer[0],
  .stack_size = sizeof(TaskBuffer),
  .cb_mem = &TaskControlBlock,
  .cb_size = sizeof(TaskControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
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
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
void StartDefaultTask(void *argument);
void Task01(void *argument);
void Task02(void *argument);
void Task03(void *argument);
void Task04(void *argument);
void Task05(void *argument);
void Task06(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void FEES_print(int a , uint8_t PrintBuffer[] ){

  #ifdef WINDOWS
  cout << PrintBuffer;
  #endif // WINDOWS

  #ifdef FREERTOS
	switch(a){
        case 1:  HAL_UART_Transmit(&huart1,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 2:  HAL_UART_Transmit(&huart2,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 3:  HAL_UART_Transmit(&huart3,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 4:  HAL_UART_Transmit(&huart6,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 6:  HAL_UART_Transmit(&huart6,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
      default:   HAL_UART_Transmit(&huart2,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
    }
    #endif // FREERTOS
}

void FEES_scan(int a, char ScanBuffer[] ){

	switch(a){
        case 1:  HAL_UART_Receive_DMA(&huart1, ScanBuffer, strlen(ScanBuffer));
        break;
        case 2:  HAL_UART_Receive_DMA(&huart2, ScanBuffer, strlen(ScanBuffer));
        break;
        case 3:  HAL_UART_Receive_DMA(&huart3, ScanBuffer, strlen(ScanBuffer));
        break;
        case 4:  HAL_UART_Receive_DMA(&huart6, ScanBuffer, strlen(ScanBuffer));
        break;
        case 6:  HAL_UART_Receive_DMA(&huart6, ScanBuffer, strlen(ScanBuffer));

      default:   HAL_UART_Receive_DMA(&huart2, ScanBuffer, strlen(ScanBuffer));
        break;
    }
}

#define GETCHAR_PROTOTYPE int __io_getchar (void)

GETCHAR_PROTOTYPE
{
  char * getbuffer = 0;
  __HAL_UART_CLEAR_OREFLAG(&huart1);
  HAL_UART_Receive(&huart1, getbuffer, 1, 100);
//  HAL_UART_Transmit(&huart1, getbuffer, 1, 100);
  return &getbuffer;
}


int Serial_Scanf(char *ptr, int len)
{

  int DataIdx = 0;
  uint8_t thechar;
  thechar= ' ';
  while(thechar!= '\n' && thechar != '\r' && DataIdx<len)
  { thechar = __io_getchar();

  if ( thechar  >= 0xFF){
    FEES_print(1, "\n\r  !!! Please enter a valid ASCII character \n");
    return 0xFF;}
  *ptr++ =thechar;
  DataIdx+=1;
  }
  return DataIdx;
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
  MX_USART2_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */


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
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task1 */
  Task1Handle = osThreadNew(Task01, NULL, &Task1_attributes);

  /* creation of Task2 */
  Task2Handle = osThreadNew(Task02, NULL, &Task2_attributes);

  /* creation of Task3 */
  Task3Handle = osThreadNew(Task03, NULL, &Task3_attributes);

  /* creation of Task4 */
  Task4Handle = osThreadNew(Task04, NULL, &Task4_attributes);

  /* creation of Task5 */
  Task5Handle = osThreadNew(Task05, NULL, &Task5_attributes);

  /* creation of Task6 */
  Task6Handle = osThreadNew(Task06, NULL, &Task6_attributes);

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
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV6;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 160-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 25-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 50-1;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 75-1;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 160-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 50-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

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

  /*Configure GPIO pin : PGOOD_Pin */
  GPIO_InitStruct.Pin = PGOOD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PGOOD_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  Hardware_Watchdog_Refresh();
	  // TestPins();
	  // pintoggle('d',15);  	// CS_NAND - Led BLU
	  //PWM_STARTERS_T2_3_VariablePWM();

	  osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Task01 */
/**
* @brief Function implementing the Task1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task01 */
void Task01(void *argument)
{
  /* USER CODE BEGIN Task01 */
  /* Infinite loop */
  for(;;)
  {
	  //Main_FEES();


	  FEES_print(1 , "CIAO , che dici? si o no? \n " );
	  char scanbuffer[5];

	  FEES_scan( 1, scanbuffer);

	  if(scanbuffer[0]=='y'){
		  FEES_print(1 , "you said yes! \n" );
	  }
	  if(scanbuffer[0]=='n'){
		  FEES_print(1 , "you said no! \n" );
	  }


/*

	  FEES_print(1 , "\r    __________________________________________________  \n" );
	  FEES_print(1 , "\r   |                                                  | \n" );
	  FEES_print(1 , "\r   |                                                  | \n" );
	  FEES_print(1 , "\r   |                                                  | \n" );
	  FEES_print(1 , "\r   |                                                  | \n" );
	  FEES_print(1 , "\r   |__________________________________________________| \n" );

*/


/*

	  FEES_print(1 , "1 \n" );
	  FEES_print(2 , "2 \n" );
	  FEES_print(3 , "3 \n" );
	  FEES_print(6 , "6 \n" );

*/

	  osDelay(1000);
  }
  /* USER CODE END Task01 */
}

/* USER CODE BEGIN Header_Task02 */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task02 */
void Task02(void *argument)
{
  /* USER CODE BEGIN Task02 */
	/* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }

  /* USER CODE END Task02 */
}

/* USER CODE BEGIN Header_Task03 */
/**
* @brief Function implementing the Task3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task03 */
void Task03(void *argument)
{
  /* USER CODE BEGIN Task03 */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END Task03 */
}

/* USER CODE BEGIN Header_Task04 */
/**
* @brief Function implementing the Task4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task04 */
void Task04(void *argument)
{
  /* USER CODE BEGIN Task04 */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END Task04 */
}

/* USER CODE BEGIN Header_Task05 */
/**
* @brief Function implementing the Task5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task05 */
void Task05(void *argument)
{
  /* USER CODE BEGIN Task05 */
  /* Infinite loop */
  for(;;)
  {
	osDelay(1);
  }
  /* USER CODE END Task05 */
}

/* USER CODE BEGIN Header_Task06 */
/**
* @brief Function implementing the Task6 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task06 */
void Task06(void *argument)
{
  /* USER CODE BEGIN Task06 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task06 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
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
