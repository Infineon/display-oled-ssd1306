/******************************************************************************
 * \file LCDConf.h
 *
 * Description: This file is needed to support the existing include scheme
 * dictated by emWin.
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

#pragma once

/**
* \addtogroup group_board_libs SSD1306 OLED Display
* \{
* Support functions that allow the u8g2 graphics library to work with the
* SSD1306 OLED display.
*/

#if defined(COMPONENT_U8G2)

#include "cyhal_i2c.h"
#include "u8g2.h"

#if defined(__cplusplus)
extern "C"
{
#endif

//
// Physical display size
//
#define MTB_DISPLAY_SIZE_X       128
#define MTB_DISPLAY_SIZE_Y       64
#define MTB_DISPLAY_COLOR_BITS   1


#if defined(__cplusplus)
}
#endif

#endif /* defined(COMPONENT_U8G2) */

/** \} group_board_libs */
