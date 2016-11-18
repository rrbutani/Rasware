#include "RASDemo.h"

#include <RASLib/inc/common.h>
#include <RASLib/inc/linesensor.h>

static tLineSensor *gls;
static tBoolean initialized = false;

void initGPIOLineSensor(void) {
    // don't initialize this if we've already done so
    if (initialized) {
        return;
    }

    initialized = true;

    // use 8 I/O pins to initialize a GPIO line sensor
    gls = InitializeGPIOLineSensor(
        PIN_B3,
        PIN_C4,
        PIN_C5,
        PIN_C6,
        PIN_C7,
        PIN_D6,
        PIN_D7,
        PIN_F4
        );
}

void gpioLineSensorDemo(void) {
    Printf("Press any key to quit\n");

    // loop as long as the user doesn't press a key
    while (!KeyWasPressed()) {
        int i;
        float line[8];

        // put the values of the line sensor into the 'line' array
        LineSensorReadArray(gls, line);
        Printf("Line Sensor: [");

        for (i = 0; i < 8; i++) {
            Printf("%.2f ", line[i]);
        }

        Printf("\b]        \r");
    }

    Printf("\n");
}
