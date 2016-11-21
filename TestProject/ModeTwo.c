#include "modes.h"

#include "Hardware.h"
#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>
#include <TechnicalDifficulties/inc/lights.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>

void modeTwoInitLights(void)
{
	OneColor(0xFF, 0x88, 0x00);
}

void modeTwoStepLights(void)
{

}

void ModeTwo(tBoolean *running, tBoolean rightSide)
{
	while(*running)
	{
		Printf("Mode Two; Right Side is a %d\n", rightSide);

		Wait(0.1f);
	}
}