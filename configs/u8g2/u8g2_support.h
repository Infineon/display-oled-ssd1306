/******************************************************************************
 * \file u8g2_support.h
 *
 * Description: This file contains the support functions used by the u8g2
 * graphics library.
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

/**
 * \addtogroup group_board_libs SSD1306 OLED Display
 * \{
 * Support functions that allow the u8g2 graphics library to work with the
 * SSD1306 OLED display.
 */

#if defined(COMPONENT_U8G2)

#include "mtb_ssd1306_i2c.h"
#include "cyhal_i2c.h"
#include "u8g2.h"

#if defined(__cplusplus)
extern "C"
{
#endif


/*******************************************************************************
 * Function Name: u8x8_byte_hw_i2c
 ********************************************************************************
 *
 * Summary:
 *  This is a hardware abstraction layer for the u8x8 library
 *
 *  Return: Status - Return 1 for a valid case, 0 for an invalid case
 *
 *  Inputs:
 *     *u8x8:    Pointer to a OLED structure
 *     msg:      The type of I2C message to send (start, send bytes, or stop))
 *     arg_int:  The number of bytes to send
 *     *arg_ptr: Pointer to the bytes to send
 *
 *  Note: No error checking is done on the I2C transactions
 ********************************************************************************/
uint8_t u8x8_byte_hw_i2c(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int, void* arg_ptr);


/*******************************************************************************
 * Function Name: u8x8_gpio_and_delay_cb
 ********************************************************************************
 *
 * Summary:
 *  This is a callback function used by the u8x8 library. It is used to add
 *  a delay using the available PSoC™ delay functions.
 *
 *  The delay can be a specified number of milliseconds, 10 microseconds, or 100 nanoseconds
 *
 *  Return: Status - Return 1 for a valid case, 0 for an invalid case
 *
 *  Inputs:
 *     *u8x8:    Unused but required since the u8x8 library call provides it
 *     msg:      The type of delay (x milliseconds, 10 microseconds, or 100 nanoseconds)
 *     arg_int:  The delay in milliseconds (for the mm\illisecond delay type)
 *     *arg_ptr: Unused but required since the u8x8 library call provides it
 ********************************************************************************/
uint8_t u8x8_gpio_and_delay_cb(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int, void* arg_ptr);


#if defined(__cplusplus)
}
#endif

#endif // defined(COMPONENT_U8G2)

/** \} group_board_libs */
