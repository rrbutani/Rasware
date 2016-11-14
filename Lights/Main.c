#include <stdint.h>
#include <stdbool.h>

#include "RASLib/inc/WS2812_drv.h"
#include "RASLib/inc/SPI_uDMA_drv.h"
#include "samplePatterns.h"

#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

#include "inc/hw_memmap.h"
#include "driverlib/cpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


int main(void)
{
    //
    // An array to hold the colors.  30 LEDs for this example, each has a red,
    // green, and blue intensity.  Note that these are actually stored GRB,
    // because WS2812b LEDs are weird.
    //
    static uint8_t pui8Colors[30][3];

    //
    // The output array for the SPI bus.  The nature of the timing for the LEDs
    // makes it so we can't just map a single intensity byte onto a single byte
    // to transmit out the SPI peripheral.  Instead, we separate each bit of
    // the intensity to four bits of SPI out.  The WS one wire protocol
    // basically boils down to "110" on the SPI bus is read as a 1 by the LED,
    // "100" is a 0.  We use some macros to figure out how many bytes of SPI
    // array we need to represent each of the 30 LEDs.
    //
    static uint8_t pui8SPIOut[30][WS2812_SPI_BYTE_PER_CLR * 
                                  WS2812_SPI_BIT_WIDTH];

    //
    // We'll pass this flag to the uDMA library, which will tell us when each
    // transfer is done.  This is only necessary if you want the update rate of
    // the LED strip to be based on how fast the data can be read by the WSB LED
    //
    uint8_t ui8SPIDone;
    int i;

    //
    // Set the clocking to run from the PLL at 50MHz
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    //
    // This is in every example ever.  It involves how floating point values
    // get passed around... ignore it.
    //
    ROM_FPULazyStackingEnable();

    //
    // Initialize the UART and say hello.
    //
    // Printf("DMA!!\n");

    //
    // Initialize the color array to be evenly spaced along the color wheel.
    //
    rainbowInit(pui8Colors, 30);

    //
    // Initialize and start the inifinite uDMA transfers
    //
    InitSPITransfer((uint8_t*)pui8SPIOut, sizeof(pui8SPIOut), &ui8SPIDone);

    while(1)
    {
        //
        // Check to see if the SPI buffer is done sending out data
        //
      // Printf("DMA!!\n");
        if(ui8SPIDone)
        {
            ui8SPIDone = 0;
            for(i=0;i<30;i++)
            {
                //
                // Update the RGB colors to the next value in the color wheel
                //
                rainbowShift(&(pui8Colors[i][0]), &(pui8Colors[i][1]),
                             &(pui8Colors[i][2]));
                //
                // Update the SPI transmit array to reflect the new RGB values
                //
                WSGRBtoSPI(pui8SPIOut[i], pui8Colors[i][0],
                           pui8Colors[i][1], pui8Colors[i][2]);
            }

            //
            // Tell the processor to stop executing instructions and relax
            // while the uDMA engine finishes its job.
            //
            // CPUwfi();
        }
    }
}
