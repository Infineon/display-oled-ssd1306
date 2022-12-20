/******************************************************************************
 * \file mtb_ssd1306_i2c.h
 *
 * Description: This file contains details about the SSD1306 display and
 * functions necessary to communicate with it.
 *
 *******************************************************************************
 * \copyright
 * Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#pragma once

#if defined(__cplusplus)
extern "C"
{
#endif

#include "cyhal_i2c.h"

#define OLED_I2C_ADDRESS  (0x3C)

//
// Physical display size
//
#define MTB_DISPLAY_SIZE_X       128
#define MTB_DISPLAY_SIZE_Y       64
#define MTB_DISPLAY_COLOR_BITS   1

/**
 * Allows u8g2_support.c to access the i2c_ptr
 *
 * @return cyhal_i2c_t  Pointer to the I2C object used to communicate with the OLED display
 */
cyhal_i2c_t* mtb_ssd1306_get_i2c_ptr(void);

/**
 * This function writes a command byte to the display controller with A0 = 0
 * NOTE: This function signature is defined by emWin
 *
 * @param[in] c command to be written to the display controller
 */
void mtb_ssd1306_write_command_byte(uint8_t c);

/**
 * This function writes a data byte to the display controller with A0 = 1
 * NOTE: This function signature is defined by emWin
 *
 * @param[in] c data to be written to the display controller
 */
void mtb_ssd1306_write_data_byte(uint8_t c);

/**
 * This function writes multiple data bytes to the display controller with A0 = 1
 * NOTE: This function signature is defined by emWin
 *
 * @param[in] pData     Pointer to the buffer that has data
 * @param[in] numBytes  Number of bytes to be written to the display controller
 */
void mtb_ssd1306_write_data_stream(uint8_t* pData, int numBytes);

#if defined(__cplusplus)
}
#endif
