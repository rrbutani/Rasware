#include <EVOM.h>

#include <RASLib/inc/servo.h>
#include <RASLib/inc/motor.h>

#include <TechnicalDifficulties/inc/params.h>

void ArmsUp(tServo *lArm, tServo *rArm)
{
	SetServo(lArm, ARM_UP_POSITION);
	SetServo(rArm, ARM_UP_POSITION);
}

void ArmsDown(tServo *lArm, tServo *rArm)
{
	SetServo(lArm, 1.0f);
	SetServo(rArm, 1.0f);
}

void Intake(tMotor *intake)
{
	SetMotor(intake, 1.0f);
}

void Extake(tMotor *intake)
{
	SetMotor(intake, 1.0f);
}

void StopIntake(tMotor *intake)
{
	SetMotor(intake, 0.0f);
}