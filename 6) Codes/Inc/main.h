/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define buzz_Pin GPIO_PIN_0
#define buzz_GPIO_Port GPIOA
#define MSFR_RELAY_Pin GPIO_PIN_3
#define MSFR_RELAY_GPIO_Port GPIOA
#define RELAY_Pin GPIO_PIN_10
#define RELAY_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_15
#define LED_1_GPIO_Port GPIOB
#define PB1_Pin GPIO_PIN_11
#define PB1_GPIO_Port GPIOD
#define PB2_Pin GPIO_PIN_12
#define PB2_GPIO_Port GPIOD
#define PB3_Pin GPIO_PIN_13
#define PB3_GPIO_Port GPIOD
#define PB4_Pin GPIO_PIN_7
#define PB4_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */




#define   DAC_CH_X         DAC_CHANNEL_1
#define   DAC_CH_Y         DAC_CHANNEL_2
#define Reference_Voltage  3300.00 //milivolt
#define Resolution         4096.00    //use dac 12 bit
//v output step on 12 bit is 0.8milivolt or 800uV


//=================================================================
#define   READ_ADC_CH_HV_PDUCL_PX         1//ADC1_IN6	PIN31  //PDTA1
#define   READ_ADC_CH_HV_PDUCL_PY         2//ADC1_IN7	PIN32  //PDTA2
#define   READ_ADC_CH_HV_PDU_MX			  3//ADC1_IN14			//PDTA3
#define   READ_ADC_CH_HV_PDU_MY			  4//ADC1_IN15			//PDTA4
#define   READ_ADC_SENS1	              5//ADC1_IN8
#define   READ_ADC_SENS2				  6// ADC1_IN9


#define  PDU_POWER(x)            (x ? (HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET)):(HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin,GPIO_PIN_RESET)))
#define  RELAY_USER_INT(x)       (x ? (HAL_GPIO_WritePin(MSFR_RELAY_GPIO_Port, MSFR_RELAY_Pin, GPIO_PIN_SET)):(HAL_GPIO_WritePin(MSFR_RELAY_GPIO_Port, MSFR_RELAY_Pin,GPIO_PIN_RESET)))

#define LED_TOGG                     HAL_GPIO_TogglePin( LED_1_GPIO_Port ,LED_1_Pin )


#define  SET_BUZZ(x)            (!x ? (HAL_GPIO_WritePin(buzz_GPIO_Port, buzz_Pin, GPIO_PIN_SET)):(HAL_GPIO_WritePin(buzz_GPIO_Port, buzz_Pin,GPIO_PIN_RESET)))


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
