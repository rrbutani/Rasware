#include "modes.h"

#include "Hardware.h"
#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>
#include <TechnicalDifficulties/inc/lights.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>

void modeThreeInitLights(void)
{
	OneColor(0xFF, 0xFF, 0x00);
}

void modeThreeStepLights(void)
{

}

void ModeThree(tBoolean *running, tBoolean rightSide)
{
	while(*running)
	{
		Printf("Mode Three; Right Side is a %d\n", rightSide);

		Wait(0.1f);
	}
}