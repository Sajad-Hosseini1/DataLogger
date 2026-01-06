/*
 * stm32f1xx_it.c
 *
 *  Created on: Oct 9, 2025
 *      Author: sajad
 */

#include "main.h"
#include "stm32f1xx_it.h"
#include "adc.h"
#include "tim.h"
#include "rtc.h"
#include "uart.h"


extern PCD_HandleTypeDef hpcd_USB_FS;

void SysTick_Handler(void)
{
	HAL_IncTick();
}


void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief ADC Callback
 */
void ADC1_2_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&adc1Handle);
}


/**
 * @brief DMA Interrupt Handler
 */
void DMA1_Channel1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(adc1Handle.DMA_Handle);
}


/*
 * @brief TIM3 INT Handler
 */
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
}


/**
 * @brief RTC Alarm Interrupt Handler
 */
void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&hrtc);
}


/**
  * @brief UART
  */
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart1_tx);
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart1_rx);
}


