#ifndef TD_PARAMS   /* Include guard */
#define TD_PARAMS

#include <RASLib/inc/gpio.h>

//*********************************Hardware************************************

/* NOTE:
 * A6 and A7 are broken (for I2C at least)!
 */

//IR Sensors - Analog ADC Read Pins
static const tPin IR_Front_Right = PIN_D0;
static const tPin IR_Front_Left  = PIN_D1;
static const tPin IR_Back_Right  = PIN_D2;
static const tPin IR_Back_Left   = PIN_D3;

//MPU-6050:
static const tPin MPU_SDA = PIN_B3;
static const tPin MPU_SCL = PIN_B2;

//Drive Servos:
static const tPin DRIVE_RIGHT = PIN_B7;
static const tPin DRIVE_LEFT  = PIN_B6;

//Intake Servo:
static const tPin INTAKE = PIN_C4;

//Lights:
/*NOTE: This variable isn't actually used; you can't use this to change the
 *data pin for the strip. Due to the SPI DMA, the data pin for the strip must
 *be F1 (for now). This is here mainly for reference - and so F1 isn't
 *mistakenly used for something else.
 */
static const tPin LEDStrip_Data = PIN_F1;

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
static const tPin LEFT_RIGHT_TOGGLE = PIN_A2;
static const tPin START_STOP_BUTTON = PIN_F0;
static const tPin MODE_CYCLE_BUTTON = PIN_F4;

//*****************************************************************************


#endif // TD_PARAMS
