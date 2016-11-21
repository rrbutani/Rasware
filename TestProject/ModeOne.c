#include "modes.h"

#include "Hardware.h"
#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>
#include <TechnicalDifficulties/inc/lights.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>
#include <TechnicalDifficulties/inc/EVOM.h>

void modeOneInitLights(void)
{
	OneColor(0xff, 0x00, 0x00);
}

void modeOneStepLights(void)
{

}

void ModeOne(tBoolean *running, tBoolean rightSide)
{
	while(*running)
	{
		Printf("Mode One; Right Side is a %d\n", rightSide);

		// Wait(0.1f);
		//  ArmsUp(leftArm, rightArm);
		Intake(intake);//Start spinning intake
		TurnLeft(0.6f);
		Wait(0.3f);
		DriveForward(leftMotor, rightMotor, 0.5f);
		Wait(1.35f);
		TurnRight(0.6f);
		Wait(0.5f);
		LineFollow();

	}
}
