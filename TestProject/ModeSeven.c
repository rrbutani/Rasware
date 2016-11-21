#include "modes.h"

#include "Hardware.h"
#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>
#include <TechnicalDifficulties/inc/lights.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>

void modeSevenInitLights(void)
{
	OneColor(0x88, 0x88, 0xFF);
}

void modeSevenStepLights(void)
{

}

void ModeSeven(tBoolean *running, tBoolean rightSide)
{
	while(*running)
	{
		Printf("Mode Seven; Right Side is a %d\n", rightSide);

		Wait(0.1f);
	}
}