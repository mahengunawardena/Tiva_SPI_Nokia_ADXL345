
/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"

int main(void)
{
    // Board Service Package









    char *pcChars = "SSI Master send data.";
    int32_t i32Idx;
    int32_t temp;

    // Set the clocking to run directly from the external crystal/oscillator.
    // SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);
    //
    // Enable the SSI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    //
    // Wait for the SSI0 module to be ready.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
    {
    }
    //
    // Configure the SSI.
    //
    temp=SysCtlClockGet()/1000;
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER, 2000000, 8);
    //
    // Enable the SSI module.
    //
    SSIEnable(SSI0_BASE);
    //
    // Send some data.
    //
    i32Idx = 0;
    while (pcChars[i32Idx])
    {
        SSIDataPut(SSI0_BASE, pcChars[i32Idx]);
        i32Idx++;
    }

    return 0;
}
