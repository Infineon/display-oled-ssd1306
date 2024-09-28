/******************************************************************************
 * \file mtb_ssd1306.c
 *
 * Description: This file contains code necessary to communicate with the
 * OLED display.
 *
 *******************************************************************************
 * \copyright
 * Copyright 2018-2024 Cypress Semiconductor Corporation (an Infineon company) or
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

#include <string.h>

#include "mtb_ssd1306_i2c.h"
#include "mtb_ssd1306.h"

#define OLED_CONTROL_BYTE_CMD       (0x00)
#define OLED_CONTROL_BYTE_DATA      (0x40)

static cyhal_i2c_t* _mtb_ssd1306_i2c_ptr;


//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_init_i2c
//
// Initialize the OLED display.
//--------------------------------------------------------------------------------------------------
cy_rslt_t mtb_ssd1306_init_i2c(cyhal_i2c_t* i2c_inst)
{
    if (i2c_inst == NULL)
    {
        return CY_RSLT_SSD1306_INIT_FAIL;
    }

    _mtb_ssd1306_i2c_ptr = i2c_inst;

    return CY_RSLT_SUCCESS;
}


//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_free
//
// Free the resources used with the OLED display.
//--------------------------------------------------------------------------------------------------
void mtb_ssd1306_free(void)
{
    _mtb_ssd1306_i2c_ptr = NULL;
}


//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_get_i2c_ptr
//
// Allows u8g2_support.c to access the _mtb_ssd1306_i2c_ptr
//--------------------------------------------------------------------------------------------------
cyhal_i2c_t* mtb_ssd1306_get_i2c_ptr(void)
{
    return _mtb_ssd1306_i2c_ptr;
}


//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_write_command_byte
//
// This function writes a command byte to the display controller
//--------------------------------------------------------------------------------------------------
void mtb_ssd1306_write_command_byte(uint8_t c)
{
    // The first byte of the buffer tells the display that the following byte is a command
    uint8_t buff[2] = { OLED_CONTROL_BYTE_CMD, c };

    // Write the buffer to display controller
    cy_rslt_t rslt =
        cyhal_i2c_master_write(_mtb_ssd1306_i2c_ptr, OLED_I2C_ADDRESS, buff, 2, 0, true);
    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
}


//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_write_data_byte
//
// This function writes a data byte to the display controller
//--------------------------------------------------------------------------------------------------
void mtb_ssd1306_write_data_byte(uint8_t c)
{
    // First byte of the buffer tells the display controller that the following byte is a data byte
    uint8_t buff[2] = { OLED_CONTROL_BYTE_DATA, c };

    // Write the buffer to display controller
    cy_rslt_t rslt =
        cyhal_i2c_master_write(_mtb_ssd1306_i2c_ptr, OLED_I2C_ADDRESS, buff, 2, 0, true);
    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
}


CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Directive 4.6', 1,
                             'emWin expects variable numBytes to be int type.');
//--------------------------------------------------------------------------------------------------
// mtb_ssd1306_write_data_stream
//
// This function writes multiple data bytes to the display controller
//--------------------------------------------------------------------------------------------------
void mtb_ssd1306_write_data_stream(uint8_t* pData, int numBytes)
{
    CY_MISRA_BLOCK_END('MISRA C-2012 Directive 4.6');
    CY_ASSERT(numBytes <= MTB_DISPLAY_SIZE_X);
    uint8_t buff[MTB_DISPLAY_SIZE_X + 1];

    // Tell the display controller that the following bytes are data bytes
    buff[0] = OLED_CONTROL_BYTE_DATA;
    memcpy(&buff[1], pData, numBytes);

    // Write all the data bytes to the display controller
    cy_rslt_t rslt = cyhal_i2c_master_write(_mtb_ssd1306_i2c_ptr, OLED_I2C_ADDRESS, buff,
                                            numBytes+1, 0, true);
    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
}
