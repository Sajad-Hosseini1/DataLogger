/*
 * exti.c
 *
 *  Created on: Oct 21, 2025
 *      Author: sajad
 */

#include "exti.h"

/**
 * @brief Push-Buttin EXTI configuration
 */
void exti_buttonConfig(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  HAL_NVIC_SetPriority(EXTI0_IRQn, 0xF, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
