
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
    // Board Support Package

    // Set the clocking to run directly from the external crystal/oscillator.
    // Use the PLL (400 MHz to generate 400 MHz clock
    // Divide 400 MHz / 2 = 200 MHz
    // Divide 200 MHz / SYSCTL_SYSDIV_4 to generate a 20MHz Clock
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_10);


    return 0;
}
