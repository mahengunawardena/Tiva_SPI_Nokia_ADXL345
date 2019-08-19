/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "Tiva_spi.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
int main(void)
{
    int32_t temp;
    uint32_t buffer;
    buffer = 0;

    // Board Support Package


    /********************************************************************************************/

    // Set the clocking to run directly from the external crystal/oscillator.
    // Use the PLL (400 MHz to generate 400 MHz clock
    // Divide 400 MHz / 2 = 200 MHz
    // Divide 200 MHz / SYSCTL_SYSDIV_4 to generate a 20MHz Clock
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_10);

     temp = SysCtlClockGet() / 1000;

    initSPI3();

    while (1)
    {
        while (SSIBusy(SSI3_BASE)) ;
        SSIDataPut(SSI3_BASE, 0x80); //Puts a data element into the SSI transmit FIFO
        while (SSIBusy(SSI3_BASE));
        SSIDataGet(SSI3_BASE, &buffer);
     }

    return 0;
}
