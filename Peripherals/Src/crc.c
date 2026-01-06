/*
 * crc.c
 *
 *  Created on: Nov 6, 2025
 *      Author: sajad
 */


#include "crc.h"

CRC_HandleTypeDef hcrc;

/**
 * @brief CRC Configuration
 */
bool crc_config(void)
{
  __HAL_RCC_CRC_CLK_ENABLE();
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    return false;
  }
  return true;
}
