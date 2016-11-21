#include "modes.h"

#include "Hardware.h"
#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>
#include <TechnicalDifficulties/inc/lights.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>

void modeEightInitLights(void)
{
	OneColor(0x00, 0x00, 0xFF);
}

void modeEightStepLights(void)
{

}

void ModeEight(tBoolean *running, tBoolean rightSide)
{
	while(*running)
	{
		Printf("Mode Eight; Right Side is a %d\n", rightSide);

		Wait(0.1f);
	}
}