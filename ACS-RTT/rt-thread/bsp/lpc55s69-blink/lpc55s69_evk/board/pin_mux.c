/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v6.0
processor: LPC55S69
package_id: LPC55S69JBD100
mcu_data: ksdk2_0
processor_version: 6.0.0
board: LPCXpresso55S69
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Enable IOCON Clock */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    /* Flexcomm0 as USART */
    IOCON->PIO[0][29] = (IOCON_FUNC1  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );   // Debug Usart RXD pin
    IOCON->PIO[0][30] = (IOCON_FUNC1  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // Debug Usart TXD pin

    /* ADC0 */
    IOCON->PIO[0][23] = (IOCON_FUNC0  | IOCON_MODE_INACT  | IOCON_ANALOG_EN  | IOCON_AWS_EN);  // PIO0_23 ADC0_0

    /* SDIO */
    IOCON->PIO[0][15] = (IOCON_FUNC5  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Write Protect
    IOCON->PIO[0][17] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Card Detect
    IOCON->PIO[0][24] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Data0
    IOCON->PIO[0][25] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Data1
    IOCON->PIO[0][31] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Data2
    IOCON->PIO[0][ 7] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO CLK
    IOCON->PIO[0][ 8] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO CMD
    IOCON->PIO[0][ 9] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Power Enable
    IOCON->PIO[1][ 0] = (IOCON_FUNC2  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDIO Data3

    /* High Speed SPI */
    IOCON->PIO[1][ 2] = (IOCON_FUNC6  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SPI8_SCK
    IOCON->PIO[0][26] = (IOCON_FUNC9  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SPI8_MOSI
    IOCON->PIO[1][ 3] = (IOCON_FUNC6  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SPI8_MISO

    /* GPIO -- LED */
    IOCON->PIO[1][7]  = (IOCON_FUNC0  | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN );  // LED GREEN
    IOCON->PIO[1][6]  = (IOCON_FUNC0  | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN );  // LED RED
    
    /* CTIMER2 Match 1 */
    IOCON->PIO[1][4]  = (IOCON_FUNC3  | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN );  // LED BLUE
    
    /* Flexcomm2 as USART */
    IOCON->PIO[0][27] = (IOCON_FUNC1  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // mikro BUS Usart TXD pin
    IOCON->PIO[1][24] = (IOCON_FUNC1  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // mikro BUS Usart TXD pin
    
    /* Flexcomm4 as I2C */
    IOCON->PIO[1][20] = (IOCON_FUNC5  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SCL
    IOCON->PIO[1][21] = (IOCON_FUNC5  | IOCON_MODE_INACT  | IOCON_DIGITAL_EN );  // SDA
    
    /* Disable IOCON Clock -- To Save Power */
    CLOCK_DisableClock(kCLOCK_Iocon);
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
