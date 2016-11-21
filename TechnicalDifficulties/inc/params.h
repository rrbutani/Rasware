#ifndef TD_PARAMS   /* Include guard */
#define TD_PARAMS

#include <RASLib/inc/gpio.h>

//*********************************Hardware************************************

/* NOTE:
 * A6 and A7 are broken (for I2C at least)!
 */

//IR Sensors - Analog ADC Read Pins
static const tPin IR_FRONT_RIGHT = PIN_E1;
static const tPin IR_FRONT_LEFT  = PIN_D1;
static const tPin IR_BACK_RIGHT  = PIN_D2;
static const tPin IR_BACK_LEFT   = PIN_D3;

//MPU-6050:
static const tPin MPU_SDA = PIN_B3;
static const tPin MPU_SCL = PIN_B2;

//Drive Servos:
static const tPin DRIVE_RIGHT = PIN_B7;
static const tPin DRIVE_LEFT  = PIN_B6;

//Intake Servo:
static const tPin INTAKE = PIN_C4;

//Light Strip:
/*NOTE: This variable isn't actually used; you can't use this to change the
 *data pin for the strip. Due to the SPI DMA, the data pin for the strip must
 *be F1 (for now). This is here mainly for reference - and so F1 isn't
 *mistakenly used for something else.
 */
static const tPin LEDStrip_Data = PIN_F1;

//RGB LEDs:
static const tPin ONBOARD_R = PIN_D0; //PIN_F1; //Avoiding conflict w/Light
static const tPin ONBOARD_G = PIN_F3;			//strip, using filler pin D0
static const tPin ONBOARD_B = PIN_F2;			//(known to be broken)

//Arm Servos:
static const tPin ARM_RIGHT = PIN_C5;
static const tPin ARM_LEFT  = PIN_C6;

//Line Sensors (from left to right)
static const tPin LINE_1 = PIN_B5;
static const tPin LINE_2 = PIN_E4;
static const tPin LINE_3 = PIN_E5;
static const tPin LINE_4 = PIN_B4;
static const tPin LINE_5 = PIN_E1;
static const tPin LINE_6 = PIN_E2;
static const tPin LINE_7 = PIN_E3;
static const tPin LINE_8 = PIN_E0;

//Buttons
static const tPin LEFT_RIGHT_TOGGLE = PIN_A2; //Positive Logic
static const tPin START_STOP_BUTTON = PIN_F0; //Negative Logic (i.e. pull-up)
static const tPin MODE_CYCLE_BUTTON = PIN_F4; //Positive Logic because Launchpads are shit
// static const tPin REVERSE_INTAKE_BUTTON = PIN_ //TODO

//*****************************************************************************

//**************************Configuration Variables****************************

static const float ARM_UP_POSITION = 0.33f;

#define LED_STRIP_LENGTH 12
#define DEBOUNCE_TIME 50000 //in Microseconds

//*****************************************************************************

#endif // TD_PARAMS
