//============================================================================
// Name        : Tiva_spi.c
// Author      : Mahendra Gunawardena
// Version     : Rev 0.01
// Copyright   : Your copyright notice
// Description : Tiva spi in C++, Ansi-style
//============================================================================
/*
 * Tiva_spi.c
 * Implementation of a spi interface
 *
 * Copyright Mahendra Gunawardena, Mitisa LLC
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdint.h>
#include <stdbool.h>
#include "Tiva_spi.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"


void initSPI3(void)
{
    uint32_t pui32DataRx;
    pui32DataRx = 0;


    //
    // Enable the SSI3 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    //
    // Wait for the SSI0 module to be ready.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI3))
    {
    }

    // For this example SSI0 is used with PortD[3:0]. The actual port and pins
    // used may be different on your part, consult the data sheet for more
    // information. GPIO port D needs to be enabled so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    //

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // CS pin of the ADXL345 should be set prior to setting Clock polarity and Clock phases.
    // This is because ASXL345 was powered up prior to setting up the host processor

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);


    //
    // Configure the pin muxing for SSI3 functions on port D0, D1, D2, and D3.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
    GPIOPinConfigure(GPIO_PD1_SSI3FSS);
    GPIOPinConfigure(GPIO_PD2_SSI3RX);
    GPIOPinConfigure(GPIO_PD3_SSI3TX);

    //
    // Configure the GPIO settings for the SSI pins. This function also gives
    // control of these pins to the SSI hardware. Consult the data sheet to
    // see which functions are allocated per pin.
    // The pins are assigned as follows:
    // PD3 - SSI3Tx
    // PD2 - SSI3Rx
    // PD1 - SSI3Fss
    // PD0 - SSI3CLK
    // TODO: change this to select the port/pin you are using.
    //

    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);

    //
    // Disable the SSI3 module.
    //
    SSIDisable(SSI3_BASE);
    //
    // Configure and enable the SSI port for SPI master mode. Use SSI3,
    // system clock supply, idle clock level low and active low clock in
    // freescale SPI mode, master mode, 5MHz SSI frequency, and 8-bit data.
    // For SPI mode, you can set the polarity of the SSI clock when the SSI
    // unit is idle. You can also configure what clock edge you want to
    // capture data on. Please reference the data sheet for more information on
    // the different SPI modes.
    //
    SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 1000000, 8);

    //
    // Enable the SSI3 module.
    //
    SSIEnable(SSI3_BASE);
    // Read any residual data from the SSI port. This makes sure the receive
    // FIFOs are empty, so we don't read any unwanted junk. This is done here
    // because the SPI SSI mode is full-duplex, which allows you to send and
    // receive at the same time. The SSIDataGetNonBlocking function returns
    // "true" when data was returned, and "false" when no data was returned.
    // The "non-blocking" function checks if there is any data in the receive
    // FIFO and does not "hang" if there isn't.
    //

    while(SSIDataGetNonBlocking(SSI3_BASE, &pui32DataRx))
    {
    }

}

