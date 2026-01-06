/*
 * uart.c
 *
 *  Created on: Oct 19, 2025
 *      Author: sajad
 */
#include "uart.h"

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_uart1_rx;
DMA_HandleTypeDef hdma_uart1_tx;

void uart_UART1_GPIO_config(void)
{


  //Enable GPIO A Clock
  __HAL_RCC_GPIOA_CLK_ENABLE();

  //PA9     ------> USART1_TX
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



  //PA10    ------> Rx
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


bool uart_UART1_config(void)
{
	__HAL_RCC_USART1_CLK_ENABLE();

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
    return false;
  }

  //DMA Setup
  //DMA1_Channel 4 --> Tx
  //DMA1_Channel 5 --> Rx
  __HAL_RCC_DMA1_CLK_ENABLE();
   //UART1 DMA - TX
   hdma_uart1_tx.Instance = DMA1_Channel4;
   hdma_uart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
   hdma_uart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
   hdma_uart1_tx.Init.MemInc = DMA_MINC_ENABLE;
   hdma_uart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
   hdma_uart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
   hdma_uart1_tx.Init.Mode = DMA_NORMAL;
   hdma_uart1_tx.Init.Priority = DMA_PRIORITY_LOW;
   if (HAL_DMA_Init(&hdma_uart1_tx) != HAL_OK)
   {
     return false;
   }

   __HAL_LINKDMA(&huart1,hdmatx,hdma_uart1_tx);
   HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
   HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

   //UART1 DMA - RX
   hdma_uart1_rx.Instance = DMA1_Channel5;
   hdma_uart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
   hdma_uart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
   hdma_uart1_rx.Init.MemInc = DMA_MINC_ENABLE;
   hdma_uart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
   hdma_uart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
   hdma_uart1_rx.Init.Mode = DMA_NORMAL;
   hdma_uart1_rx.Init.Priority = DMA_PRIORITY_LOW;
   if (HAL_DMA_Init(&hdma_uart1_rx) != HAL_OK)
   {
     return false;
   }

   __HAL_LINKDMA(&huart1,hdmarx,hdma_uart1_rx);
   HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0);
   HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

   /* USART1 interrupt Init */
   HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
   HAL_NVIC_EnableIRQ(USART1_IRQn);




  return true;
}
