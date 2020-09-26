/******************************************************************************
 * \file LCDConf.c
 *
 * Description: This file contains the support functions used by the u8g2
 * graphics library.
 *
 *******************************************************************************
 * \copyright
 * Copyright 2018-2020 Cypress Semiconductor Corporation
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

#if defined(COMPONENT_U8G2)

#include "cyhal_i2c.h"
#include "cyhal_system.h"

#include "u8g2_support.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/* I2C Timeout in ms */
#define TIMEOUT 1000

static cyhal_i2c_t *i2c_ptr;


/*******************************************************************************
*  This is a hardware abstraction layer for the u8x8 library
********************************************************************************/
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buffer[32];
    static uint8_t buf_idx = 0;

    cy_rslt_t rslt;
    uint8_t *data;

    switch(msg)
    {
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            while( arg_int > 0 )
            {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }
            break;

        case U8X8_MSG_BYTE_INIT:
            i2c_ptr = mtb_ssd1306_get_i2c_ptr();
            CY_ASSERT(i2c_ptr != NULL);
            break;

        case U8X8_MSG_BYTE_SET_DC:
            /* ignored for i2c */
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            buf_idx = 0;
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            rslt = cyhal_i2c_master_write(i2c_ptr, OLED_I2C_ADDRESS, buffer, buf_idx, 0, true);
            CY_UNUSED_PARAMETER(rslt); /* CY_ASSERT only processes in DEBUG, ignores for others */
            CY_ASSERT(CY_RSLT_SUCCESS == rslt);
            break;

        default:
            return 0;
    }
    return 1;
}


/*******************************************************************************
*  This is a callback function used by the u8x8 library. It is used to add
*  a delay using the avaialable PSoC delay functions.
********************************************************************************/
uint8_t u8x8_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    (void)u8x8;
    (void)arg_ptr;
    switch(msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: // No initialization required
            break;
        case U8X8_MSG_DELAY_MILLI:
            cyhal_system_delay_ms(arg_int);
            break;
        case U8X8_MSG_DELAY_10MICRO:
            cyhal_system_delay_us(10);
         break;
        case U8X8_MSG_DELAY_100NANO:
            cyhal_system_delay_us(1);
            break;
        /* We only use I2C in HW so none of these cases are used
         * If you want to use a software interface or have these pins then you
         * need to read and write them */
        case U8X8_MSG_GPIO_SPI_CLOCK:
        case U8X8_MSG_GPIO_SPI_DATA:
        case U8X8_MSG_GPIO_CS:
        case U8X8_MSG_GPIO_DC:
        case U8X8_MSG_GPIO_RESET:
        //case U8X8_MSG_GPIO_D0: // Same as SPI_CLOCK
        //case U8X8_MSG_GPIO_D1: // Same as SPI_DATA
        case U8X8_MSG_GPIO_D2:
        case U8X8_MSG_GPIO_D3:
        case U8X8_MSG_GPIO_D4:
        case U8X8_MSG_GPIO_D5:
        case U8X8_MSG_GPIO_D6:
        case U8X8_MSG_GPIO_D7:
        case U8X8_MSG_GPIO_E:
        case U8X8_MSG_GPIO_I2C_CLOCK:
        case U8X8_MSG_GPIO_I2C_DATA:
            break;
        default:
            return 0;
    }
    return 1;
}


#if defined(__cplusplus)
}
#endif

#endif /* defined(COMPONENT_U8G2) */
