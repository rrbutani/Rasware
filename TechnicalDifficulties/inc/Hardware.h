#ifndef TD_HW   /* Include guard */
#define TD_HW

#ifdef __cplusplus
extern "C" {
#endif

// Hardware Includes
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

// Public Init Methods
void initArms(void);
void initDrive(void);
void initIntake(void);
void initIR(void);
void initLineSensor(void);
void initButtons(void);
void initLights(void);
void initRGB(void);
void initAll(void);

#ifdef __cplusplus
}
#endif

#endif // TD_HW