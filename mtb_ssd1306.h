/******************************************************************************
 * \file mtb_ssd1306.h
 *
 * Description: This file contains code necessary to communicate with the
 * OLED display.
 *
 * \note The SSD1306 supports these I2C speed grades:
 *       * standard mode (100 kbit/s)
 *       * full speed (400 kbit/s)
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
 * Basic set of APIs for interacting with the SSD1306 OLED display.
 * This provides basic initialization and access to to the display.

 * \section subsection_board_libs_snippets Code snippets
 * \subsection subsection_board_libs_snippet_1 Snippet 1: Simple initialization with U8G2
 * The following snippet initializes the OLED display with the U8G2 graphics library.
 * \snippet mtb_ssd1306_u8g2_example.c snippet_ssd1306_u8g2_simple_init
 *
 * \subsection subsection_board_libs_snippet_2 Snippet 2: Simple text alignment with U8G2
 * The following snippet demonstrates how to use the U8G2 graphics library to align and
 * print strings to the display.
 * \snippet mtb_ssd1306_u8g2_example.c snippet_ssd1306_u8g2_display_text

 * \subsection subsection_board_libs_snippet_3 Snippet 3: Simple initialization with emWin
 * The following snippet initializes the OLED display with the emWin graphics library.
 * \snippet mtb_ssd1306_emwin_example.c snippet_ssd1306_emwin_simple_init
 *
 * \subsection subsection_board_libs_snippet_4 Snippet 4: Simple text alignment with emWin
 * The following snippet demonstrates how to use the emWin graphics library to align and
 * print strings to the display.
 * \snippet mtb_ssd1306_emwin_example.c snippet_ssd1306_emwin_display_text
 */

#include "cy_result.h"
#include "cyhal_i2c.h"

#if defined(__cplusplus)
extern "C"
{
#endif


/** Initialization failure error */
#define CY_RSLT_SSD1306_INIT_FAIL (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR,\
                                                  CY_RSLT_MODULE_BOARD_HARDWARE_SSD1306, 0))

/**
 * Initialize the I2C communication with the OLED display.
 * @param[in] i2c_inst  I2C instance to use for communicating with the SSD1306 controller.
 * @return CY_RSLT_SUCCESS if properly initialized, else an error indicating what went wrong.
 */
cy_rslt_t mtb_ssd1306_init_i2c(cyhal_i2c_t* i2c_inst);


/**
 * Frees up any resources allocated by the display as part of \ref mtb_ssd1306_init_i2c().
 */
void mtb_ssd1306_free(void);

#if defined(__cplusplus)
}
#endif

/** \} group_board_libs */
