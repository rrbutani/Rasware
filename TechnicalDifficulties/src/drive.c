#include <drive.h>

#include <RASLib/inc/servo.h>
#include <RASLib/inc/motor.h>

#include <TechnicalDifficulties/inc/params.h>

void DriveForward(tServo *lDrive, tServo *rDrive,float speed)
{
	SetMotor(lDrive, speed);
	SetServo(rDrive, speed);
}

void DriveBackward(tServo *lDrive, tServo *rDrive,float speed)
{
	SetMotor(lDrive, -speed);
	SetServo(rDrive, -speed);
}

void TurnRight(tServo *lDrive, tServo *rDrive, float speed) //turn in place
{
	SetMotor(lDrive, speed);
	SetServo(rDrive, -speed);
}

void TurnLeft(tServo *lDrive, tServo *rDrive, float speed)  //turn in place
{
	SetMotor(lDrive, -speed);
	SetServo(rDrive, speed);
}

void StopDrive(tServo *lDrive, tServo *rDrive)
{
	SetServo(lDrive, 0.0f);
	SetServo(rDrive, 0.0f);
}
