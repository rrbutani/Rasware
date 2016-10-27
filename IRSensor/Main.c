#include "RASDemo.h"

#include <RASLib/inc/common.h>
#include <RASLib/inc/adc.h>

static tADC *adc[4];
static tBoolean initialized = false;

void initIRSensor(void) {
    // don't initialize this if we've already done so
    if (initialized) {
        return;
    }

    initialized = true;

    // initialize 4 pins to be used for ADC input
    adc[0] = InitializeADC(PIN_D0);
    adc[1] = InitializeADC(PIN_D1);

}

void IRSensorDemo(void) {
    Printf("Press any key to quit\n");

    // loop as long as the user doesn't press a key
    while (!KeyWasPressed()) {
        Printf(
            "IR values:  %1.3f  %1.3f\r",
            ADCRead(adc[0]),
            ADCRead(adc[1])
            );
    }

    Printf("\n");
}
