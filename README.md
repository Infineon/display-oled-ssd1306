# OLED Display (SSD1306)

### Overview

This library provides functions to support the 128x64 pixel dot matrix OLED display driven by SSD1306 controller. This is the same display as used on the CY8CKIT-032 shield. The library has been designed to work with 3rd part graphics libraries including emWin and u8g2. The examples below show how to integrate with each of these libraries.

Additional details about this display can be found at:\n
http://www.solomon-systech.com/en/product/advanced-display/oled-display-driver-ic/ssd1306/\n
https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf

### Quick Start

* [emWin application](#emwin-application)
* [u8g2 application](#u8g2-application)

## emWin application

Follow the steps bellow in order to create a simple emWin application and display some text on it.
1. Create an empty application
2. Add this library to the application
3. Add emWin library to the application
4. Enable EMWIN_NOSNTS emWin library option by adding it to the Makefile COMPONENTS list:
```
COMPONENTS+=EMWIN_NOSNTS
```
5. Place the following code in the main.c file:
```cpp
#include "cybsp.h"
#include "mtb_ssd1306.h"
#include "GUI.h"

int main(void)
{
    cy_rslt_t result;
    cyhal_i2c_t i2c_obj;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the I2C to use with the OLED display */
    result = cyhal_i2c_init(&i2c_obj, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);

    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the OLED display */
    result = mtb_ssd1306_init_i2c(&i2c_obj);

    CY_ASSERT(result == CY_RSLT_SUCCESS);

    __enable_irq();
    GUI_Init();
    GUI_DispString("Hello world!");

    for(;;)
    {
    }
}
```
6. Build the application and program the kit.

## u8g2 application

Follow the steps bellow in order to create a simple emWin application and display some text on it.
1. Create an empty application
2. Add this library to the application
3. Add u8g2 library to the application (https://github.com/olikraus/u8g2)
4. Place the following code in the main.c file:
```cpp
#include "cybsp.h"
#include "mtb_ssd1306.h"
#include "u8g2.h"
#include "u8g2_support.h"

int main(void)
{
    cy_rslt_t result;
    cyhal_i2c_t i2c_obj;
    u8g2_t u8g2;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the I2C to use with the OLED display */
    result = cyhal_i2c_init(&i2c_obj, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the OLED display */
    result = mtb_ssd1306_init_i2c(&i2c_obj);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    __enable_irq();

    /* Initialize the U8 Display */
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_hw_i2c,
                                           u8x8_gpio_and_delay_cb);
    /* Send init sequence to the display, display is in sleep mode after this */
    u8g2_InitDisplay(&u8g2);
    /* Wake up display */
    u8g2_SetPowerSave(&u8g2, 0);

    /* Prepare display for printing */
    u8g2_SetFontPosCenter(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_crox3h_tf);
    u8g2_ClearDisplay(&u8g2);
    u8g2_ClearBuffer(&u8g2);

    /* Print a message to the display */
    const char line[] = "OLED Controller";
    uint8_t width_font = u8g2_GetUTF8Width(&u8g2, line);
    uint8_t width = u8g2_GetDisplayWidth(&u8g2);
    uint8_t height = u8g2_GetDisplayHeight(&u8g2);
    u8g2_DrawFrame(&u8g2, 0, 0, width, height);
    u8g2_DrawStr(&u8g2, (width - width_font) / 2, height / 2, line);
    u8g2_SendBuffer(&u8g2);

    for(;;)
    {
    }
}
```
5. Build the application and program the kit.

### More information

* [API Reference Guide](https://cypresssemiconductorco.github.io/display-oled-ssd1306/html/index.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Cypress Semiconductor GitHub](https://github.com/cypresssemiconductorco)
* [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)
* [PSoC 6 Code Examples using ModusToolbox IDE](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software)
* [PSoC 6 Middleware](https://github.com/cypresssemiconductorco/psoc6-middleware)
* [PSoC 6 Resources - KBA223067](https://community.cypress.com/docs/DOC-14644)

---
© Cypress Semiconductor Corporation, 2019-2020.
