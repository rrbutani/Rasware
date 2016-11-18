#ifndef TD_PARAMS   /* Include guard */
#define TD_PARAMS

#include <RASLib/inc/gpio.h>

//*********************************Hardware************************************

/* NOTE:
 * A6 and A7 are broken (for I2C at least)!
 */

//MPU-6050:
static const tPin MPU_SDA = PIN_B3;
static const tPin MPU_SCL = PIN_B2;

//Drive Servos:

//Intake Servo:

//Lights:
/*NOTE: This variable isn't actually used; you can't use this to change the
 *data pin for the strip. Due to the SPI DMA, the data pin for the strip must
 *be F1 (for now). This is here mainly for reference - and so F1 isn't 
 *mistakenly used for something else.
 */
static const tPin LEDStrip_Data = PIN_F1;

//Arm Servos:

//*****************************************************************************


#endif // TD_PARAMS