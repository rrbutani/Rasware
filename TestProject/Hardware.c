#include "Hardware.h"

// TD general includes:
#include <TechnicalDifficulties/inc/params.h>
// #include <TechnicalDifficulties/inc/shared.h>

// Hardware Includes
#include <RASLib/inc/common.h>
#include <RASLib/inc/servo.h>      //Drive Servos
#include <RASLib/inc/motor.h> 	   //Arm Servos
#include <RASLib/inc/adc.h>        //IR Sensors
#include <RASLib/inc/linesensor.h> //Line Sensor
#include <RASLib/inc/gpio.h>	   //Buttons
#include <TechnicalDifficulties/inc/imu.h> 		//Gyro
#include <TechnicalDifficulties/inc/rgbled.h>	//RGB LED
#include <TechnicalDifficulties/inc/WS2812_drv.h>
#include <TechnicalDifficulties/inc/SPI_uDMA_drv.h>
#include <TechnicalDifficulties/inc/lights.h> 

// 'Public' Pointers Variables for all hardware things
tServo *leftArm, *rightArm;
tMotor *leftDrive, *rightDrive, *intake;
tADC *fLeftIR, *fRightIR, *bLeftIR, *bRightIR;
tLineSensor *lineSensor;
tIMU *imu;
tRGB *rgb;
uint8_t ledStrip[LED_STRIP_LENGTH][3],\
		ledStripOut[LED_STRIP_LENGTH][WS2812_SPI_BYTE_PER_CLR * 
                                  WS2812_SPI_BIT_WIDTH];

static tBoolean iArms = false, iDrive = false, iIntake = false, iIR = false, \
	   iLineSensor = false, iButtons = false, iIMU = false, iLights = false, \
	   iRGB = false;


void initArms(void)
{
	if(iArms)
		return;

	iArms = !iArms;

	leftArm  = InitializeServo(ARM_LEFT);
	rightArm = InitializeServo(ARM_RIGHT);
}

void initDrive(void)
{
	if(iDrive)
		return;

	iDrive = !iDrive;

	leftDrive  = InitializeServoMotor(DRIVE_LEFT, false);
	rightDrive = InitializeServoMotor(DRIVE_RIGHT, true);
}

void initIntake(void)
{
	if(iIntake)
		return;

	iIntake = !iIntake;

	intake = InitializeServoMotor(INTAKE, false);
}

void initIR(void)
{
	if(iIR)
		return;

	iIR = !iIR;

	fLeftIR  = InitializeADC(IR_FRONT_LEFT);
	fRightIR = InitializeADC(IR_FRONT_RIGHT);
	bLeftIR  = InitializeADC(IR_BACK_LEFT);
	bRightIR = InitializeADC(IR_BACK_RIGHT);
}

void initLineSensor(void)
{
	if(iLineSensor)
		return;

	iLineSensor = !iLineSensor;

	lineSensor =    InitializeGPIOLineSensor(
						LINE_1,
						LINE_2,
						LINE_3,
						LINE_4,
						LINE_5,
						LINE_6,
						LINE_7,
						LINE_8
					);
}

void initButtons(void)
{
	if(iButtons)
		return;

	iButtons = !iButtons;

	PullDownPin(LEFT_RIGHT_TOGGLE);
	PullUpPin(START_STOP_BUTTON);
	PullDownPin(MODE_CYCLE_BUTTON);

	SetPinZ(LEFT_RIGHT_TOGGLE);
	SetPinZ(MODE_CYCLE_BUTTON);
}

void initIMU(void)
{
	if(iIMU)
		return;

	iIMU = !iIMU;

	imu = InitializeIMUObject(MPU_SDA, MPU_SCL);
}

void initLights(void)
{
	if(iLights)
		return;

	iLights = !iLights;

	InitializeLightStrip();

	OneColor(0x00, 0xFF, 0x00);
}

void initRGB(void)
{
	if(iRGB)
		return;

	iRGB = !iRGB;

	rgb = InitializeRGB(ONBOARD_R, ONBOARD_G, ONBOARD_B);
}

void InitAll(void)
{
	initArms();
	initDrive();
	initIntake();
	initIR();
	initLineSensor();
	initButtons();
	// initIMU();
	initLights();
	initRGB();
}