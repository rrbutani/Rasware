#include <stdint.h>
#include <stdbool.h>

#include <TechnicalDifficulties/inc/params.h>

#include <TechnicalDifficulties/inc/WS2812_drv.h>
#include <TechnicalDifficulties/inc/SPI_uDMA_drv.h>
#include <TechnicalDifficulties/inc/lightpatterns.h>

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

// #include <StellarisWare/inc/hw_memmap.h>
#include <StellarisWare/inc/hw_gpio.h>

// volatile uint32_t *pinMem = ((volatile uint32_t *) GPIO_PORTF_BASE + GPIO_O_DATA) + (1 << 1); //PF_1

// void flipPin(tPin pin);

// static tPin pin = PIN_A2;   //Tested across different pins; seems to be consistent (thank god)

// tTime start, end;

// void main(void)
// {
//     //Rasware cruft that we'll keep because it's esaier than rewriting:
//     InitializeGPIO();
//     GPIOPinTypeGPIOOutput(PORT_VAL(PIN_F1), PIN_VAL(PIN_F1));


//     start = GetTimeUS(); //2 ms overhead with this system/setup

//     // for(int i = 0; i < 200; i++)  //+1 ms overhead..
//     //     flipPin(pin);           //1 loop gave 12 ms (-2 + -1) = 9 ms?
//                                 //20 loop gave 197 ms -> <10 ms?
//                                 //200 gave 1946 ms -> 9.73 ms
//     // for(int i = 0; i < 10; i++)
//     // {
//     //     Wait(0.0000001);
//     // }

//     // for(int i = 0; i < 10000; i++)    
//     // {
//     //     SetPin(pin, false);     //1 run gave 7 ms (5 ms runtime then); 1 loop gave 7 as well..
//     //     SetPin(pin, true);      //2 loop gave 12 ms
//     // }                           //200 loop gave 954
//     //                             //Same results w/true and false
//                                 //Setting false then true 100 times gave 930 //perhaps indicating some loop overhead - else results would be comparable to 200 single loop
    
//     // for(int i = 0; i < 10000000; i++)  //100 run -> 54
//     // {                               //10000 run -> 5602
//     //     *pinMem = 0xff;             //100000 run -> 60002
//     //     *pinMem = 0xff;             //1000000 run -> 600003 -> 
//     //     *pinMem = 0xff;
//     // }                               //10000000 run -> 6000013 -> ~0.6 ms -> 600 ns -> 300 ns per flip? 
//                                     //      (440 ns for just high; 440 ns for just low...)
//                                     // (440 * 2) = 880 - 600 = 280 ns for for loop.
//                                     // Ergo, 600 ns is really 320ns meaning 160 ns for each set.
//                                     // Test: 3 sets should yield 760ns
//                                     // Success! It does.
//                                     // So we work with 160 ns elements.
//     //for(int k = 0; k < 100; k++)
//     tBoolean var = true;

//     while(1)
//     {         
//     for(int h = 0; h < 2; h++) //+280 ns: 1040 ns low for end bit in a pixel
//     {
//         for(int i = 0; i < 24; i++) //1080 ns for each bit in a pixel; 760 ns low bit..
//         {   //280 ns
//             if(var)
//             {
//                 *pinMem = 0xff;
//                 *pinMem = 0xff;
//                 *pinMem = 0xff;
//             }
//             *pinMem = 0xff; //160 ns
//             *pinMem = 0xff; //160 ns -> High for 320 ns
           

//             *pinMem = 0x00; 
//             *pinMem = 0x00;
//             *pinMem = 0x00; //160 ns -> Low for 480 ns + 280 ns (loop time) = 760 ns
//         }

//         for(int i = 0; i < 24; i++) //1080 ns for each bit in a pixel; 760 ns low bit..
//         {   //280 ns
//             *pinMem = 0xff; //160 ns
//             *pinMem = 0xff; //160 ns -> High for 320 ns
//             if(!var)
//             {
//                 *pinMem = 0xff;
//                 *pinMem = 0xff;
//                 *pinMem = 0xff;
//             }

//             *pinMem = 0x00; 
//             *pinMem = 0x00;
//             *pinMem = 0x00; //160 ns -> Low for 480 ns + 280 ns (loop time) = 760 ns
//         }
//     }

//     Wait(0.0000007); //Wait enough microseconds (>6) to latch..
    
//     var = !var;
//     Wait(0.10);
// }

//     // Wait(0.000004); //
//     // Wait(0.0000001); //44 w/both, 23 w/one = each takes at least 21 ms to run (plus the actual delay?)

//     end = GetTimeUS();

//     int duration = start - end;
//     Printf("%d", duration);

//     // printf("%s\n", );
// }

// void flipPin(tPin pin)
// {
//     SetPin(pin, true);
//     SetPin(pin, false);
// }

//*****************************************************************************
//
// Configure the UART and its pins to A0 and A1, which are routed to the UART
// over USB chip.  This must be called before UARTprintf().
//
//*****************************************************************************
void
configureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    // UARTStdioConfig(0, 115200, 16000000);
}

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
    // ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       // SYSCTL_XTAL_16MHZ);

    //
    // This is in every example ever.  It involves how floating point values
    // get passed around... ignore it.
    //
    // ROM_FPULazyStackingEnable();

    //
    // Initialize the UART and say hello.
    //
    // configureUART();
    // UARTprintf("\033[2JLet's do some DMA!\n");
    
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
       Printf("DMA!!\n");
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

            
            // Tell the processor to stop executing instructions and relax
            // while the uDMA engine finishes its job.
            
            CPUwfi();
        }
    }
}
