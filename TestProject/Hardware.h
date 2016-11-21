#ifndef _TD_HW_   /* Include guard */
#define _TD_HW_

#ifdef __cplusplus
extern "C" {
#endif

#include <TechnicalDifficulties/inc/params.h>

// Hardware Includes
#include <RASLib/inc/common.h>
#include <RASLib/inc/servo.h>      //Drive Servos
#include <RASLib/inc/motor.h> 	   //Arm Servos
#include <RASLib/inc/adc.h>        //IR Sensors
#include <RASLib/inc/linesensor.h> //Line Sensor
#include <RASLib/inc/gpio.h>	   //Buttons
#include <TechnicalDifficulties/inc/imu.h> 		//Gyro
#include <TechnicalDifficulties/inc/rgbled.h>	//RGB LED
// #include <TechnicalDifficulties/inc/lights.h> //TODO

// 'Public' Pointer Variables for all hardware things
extern tServo *leftArm, *rightArm;
extern tMotor *leftDrive, *rightDrive, *intake;
extern tADC *fLeftIR, *fRightIR, *bLeftIR, *bRightIR;
extern tLineSensor *lineSensor;
extern tIMU	*imu;
extern tRGB *rgb;
extern uint8_t ledStrip[LED_STRIP_LENGTH][3];

// Public Init Methods
void initArms(void);
void initDrive(void);
void initIntake(void);
void initIR(void);
void initLineSensor(void);
void initButtons(void);
void initLights(void);
void initRGB(void);
void InitAll(void);

#ifdef __cplusplus
}
#endif

#endif // _TD_HW_