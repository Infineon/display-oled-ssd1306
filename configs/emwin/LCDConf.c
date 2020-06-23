/*********************************************************************
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software  has been licensed to  Cypress Semiconductor Corporation,
whose registered  office is situated  at 198 Champion Ct. San Jose, CA
95134 USA  solely for the  purposes of creating  libraries for Cypress
PSoC3 and  PSoC5 processor-based devices,  sublicensed and distributed
under  the  terms  and  conditions  of  the  Cypress  End User License
Agreement.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Microcontroller Systems LLC
Licensed to:              Cypress Semiconductor Corp, 198 Champion Ct., San Jose, CA 95134, USA
Licensed SEGGER software: emWin
License number:           GUI-00319
License model:            Services and License Agreement, signed June 10th, 2009
Licensed platform:        Any Cypress platform (Initial targets are: PSoC3, PSoC5)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2009-06-12 - 2022-07-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "emwin.h"

#if defined(EMWIN_ENABLED)

#include "LCDConf.h"
#include "GUI.h"
#include "GUIDRV_SPage.h"


/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS MTB_DISPLAY_SIZE_X
#define YSIZE_PHYS MTB_DISPLAY_SIZE_Y

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_1

//
// Display driver, display data cache enabled
//
#define DISPLAY_DRIVER GUIDRV_SPAGE_1C1

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Defines: Configuration
*
**********************************************************************/
/* OLED display controller commands */
#define OLED_SET_CONTRAST             0x81
#define OLED_ENTIRE_DISPLAY_ON_RESUME 0xA4
#define OLED_ENTIRE_DISPLAY_ON        0xA5
#define OLED_NORMAL_DISPLAY           0xA6
#define OLED_INVERT_DISPLAY           0xA7
#define OLED_DISPLAY_OFF              0xAE
#define OLED_DISPLAY_ON               0xAF
#define OLED_SET_DISPLAY_OFFSET       0xD3
#define OLED_SET_COM_PINS             0xDA
#define OLED_SET_VCOMH_DESELECT_LEVEL 0xDB
#define OLED_SET_DISPLAY_CLOCK_DIV    0xD5
#define OLED_SET_PRECHARGE            0xD9
#define OLED_SET_MULTIPLEX            0xA8
#define OLED_SET_LOW_COLUMN           0x00
#define OLED_SET_HIGH_COLUMN          0x10
#define OLED_SET_START_LINE           0x40
#define OLED_MEMORY_MODE              0x20
#define OLED_COLUMN_ADDR              0x21
#define OLED_PAGE_ADDR                0x22
#define OLED_COM_SCAN_INC             0xC0
#define OLED_SET_COM_SCAN_DIRECTION   0xC8
#define OLED_SEGMENT_REMAP            0xA0
#define OLED_CHARGE_PUMP              0x8D
#define OLED_EXTERNAL_VCC             0x01
#define OLED_SWITCH_CAP_VCC           0x02

/* Misc settings */
#define OLED_DISPLAY_CLOCK_DIVIDE_RATIO        (0x0)
#define OLED_OSCILLATOR_FREQUENCY              (0xF)
#define OLED_DISPLAY_OFFSET                    (0x00)
#define OLED_ENABLE_CHARGE_PUMP                (0x14)
#define OLED_MEMORY_MODE_HORIZONTAL_ADDRESSING (0x00)
#define OLED_MEMORY_MODE_VERTICAL_ADDRESSING   (0x01)
#define OLED_MEMORY_MODE_PAGE_ADDRESSING       (0x02)
#define OLED_CONTRAST                          (0x8F)
#define OLED_PRECHARGE                         (0xF1)
#define OLED_VCOMH_DESELECT_LEVEL              (0x20)

#if YSIZE_PHYS == 64
    #define OLED_SET_COM_PINS_YSIZE (0x12)
#elif YSIZE_PHYS == 32
    #define OLED_SET_COM_PINS_YSIZE (0x02)
#endif

/* Scrolling #defines */
#define OLED_ACTIVATE_SCROLL                         0x2F
#define OLED_DEACTIVATE_SCROLL                       0x2E
#define OLED_SET_VERTICAL_SCROLL_AREA                0xA3
#define OLED_RIGHT_HORIZONTAL_SCROLL                 0x26
#define OLED_LEFT_HORIZONTAL_SCROLL                  0x27
#define OLED_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define OLED_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       CY8CKIT_032_InitController
*
* Purpose:
*   Initializes the display controller
*/
static void CY8CKIT_032_InitController(void)
{
    mtb_ssd1306_write_command_byte(OLED_DISPLAY_OFF);              // Command - 0xAE

    mtb_ssd1306_write_command_byte(OLED_SET_DISPLAY_CLOCK_DIV);    // Command - 0xD5
    mtb_ssd1306_write_command_byte(OLED_DISPLAY_CLOCK_DIVIDE_RATIO |
                                  (OLED_OSCILLATOR_FREQUENCY << 4));

    mtb_ssd1306_write_command_byte(OLED_SET_MULTIPLEX);            // Command - 0xA8
    mtb_ssd1306_write_command_byte(YSIZE_PHYS - 1);

    mtb_ssd1306_write_command_byte(OLED_SET_DISPLAY_OFFSET);       // Command - 0xD3
    mtb_ssd1306_write_command_byte(OLED_DISPLAY_OFFSET);

    mtb_ssd1306_write_command_byte(OLED_SET_START_LINE | 0x0);     // line #0

    mtb_ssd1306_write_command_byte(OLED_CHARGE_PUMP);              // Command - 0x8D
    mtb_ssd1306_write_command_byte(OLED_ENABLE_CHARGE_PUMP);

    mtb_ssd1306_write_command_byte(OLED_MEMORY_MODE);              // Command - 0x20
    mtb_ssd1306_write_command_byte(OLED_MEMORY_MODE_PAGE_ADDRESSING);

    mtb_ssd1306_write_command_byte(OLED_SEGMENT_REMAP | 0x1);

    mtb_ssd1306_write_command_byte(OLED_SET_COM_SCAN_DIRECTION);

    mtb_ssd1306_write_command_byte(OLED_SET_COM_PINS);             // Command - 0xDA
    mtb_ssd1306_write_command_byte(OLED_SET_COM_PINS_YSIZE);

    mtb_ssd1306_write_command_byte(OLED_SET_CONTRAST);             // Command - 0x81
    mtb_ssd1306_write_command_byte(OLED_CONTRAST);

    mtb_ssd1306_write_command_byte(OLED_SET_PRECHARGE);            // Command - 0xD9
    mtb_ssd1306_write_command_byte(OLED_PRECHARGE);

    mtb_ssd1306_write_command_byte(OLED_SET_VCOMH_DESELECT_LEVEL); // Command - 0xDB
    mtb_ssd1306_write_command_byte(OLED_VCOMH_DESELECT_LEVEL);

    mtb_ssd1306_write_command_byte(OLED_ENTIRE_DISPLAY_ON_RESUME); // Command - 0xA4

    mtb_ssd1306_write_command_byte(OLED_NORMAL_DISPLAY);           // Command - 0xA6

    mtb_ssd1306_write_command_byte(OLED_DEACTIVATE_SCROLL);

    mtb_ssd1306_write_command_byte(OLED_DISPLAY_ON);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void)
{
    CONFIG_SPAGE Config = {0};
    GUI_DEVICE * pDevice;
    GUI_PORT_API PortAPI = {0};

    //
    // Set display driver and color conversion for 1st layer
    //
    pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
    //
    // Display size configuration
    //
    LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
    LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
    //
    // Driver configuration
    //
    Config.FirstSEG = 0;
    Config.FirstCOM = 0;
    GUIDRV_SPage_Config(pDevice, &Config);
    //
    // Configure hardware routines
    //
    PortAPI.pfWrite8_A0  = mtb_ssd1306_write_command_byte;
    PortAPI.pfWrite8_A1  = mtb_ssd1306_write_data_byte;
    PortAPI.pfWriteM8_A1 = mtb_ssd1306_write_data_stream;

    /* SSD1306 is not readable through i2c. Cache is enabled
    to use display without data read operations*/

    GUIDRV_SPage_SetBus8(pDevice, &PortAPI);
    //
    // Controller configuration
    //
    GUIDRV_SPage_Set1510(pDevice);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData)
{
    int r;

    GUI_USE_PARA(LayerIndex);
    GUI_USE_PARA(pData);
    switch (Cmd)
    {
        case LCD_X_INITCONTROLLER:
            //
            // Called during the initialization process in order to set up the
            // display controller and put it into operation. If the display
            // controller is not initialized by any external routine this needs
            // to be adapted by the customer...
            //
            CY8CKIT_032_InitController();
            r = 0;
            break;

        case LCD_X_ON:
            mtb_ssd1306_write_command_byte(OLED_DISPLAY_ON);
            r = 0;
            break;

        case LCD_X_OFF:
            mtb_ssd1306_write_command_byte(OLED_DISPLAY_OFF);
            r = 0;
            break;

        default:
            r = -1;
            break;
    }
    return r;
}

#endif /* defined(EMWIN_ENABLED) */

/*************************** End of file ****************************/
