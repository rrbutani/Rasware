// #include <stdint.h>

#include "Hardware.h"
#include "modes.h"
#include <RASLib/inc/common.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/gpio.h>

#include <TechnicalDifficulties/inc//params.h>
#include <TechnicalDifficulties/inc/shared.h>

#include <TechnicalDifficulties/inc/rgbled.h>
#include <TechnicalDifficulties/inc/EVOM.h>
#include <TechnicalDifficulties/inc/lights.h>
#include <RASLib/inc/time.h>

// State Variables
static int mode = 0;
static tBoolean running = false;

// Light Variables
static uint8_t g = 0;
tBoolean flip = false;

void defaultStepLights(void)
{
	if(g == 170 || g == 0)
			flip = !flip;

	if(flip)
		g++;
	else
		g--;

	
	OneColor(0x00, g, 0x00);
}

void incrementMode(void)
{
	// If we're currently running a mode, just exit
	// The button was probably pressed accidently..
	if(running)
		return;

	// Debounce Stuff
	tTime pressed = GetTimeUS();
	tTime current = GetTimeUS();

	while((current - pressed) < DEBOUNCE_TIME)
	{
		current = GetTimeUS();

		// If, at any time in this debounce period,
		// the button is let go of (i.e. goes low
		// since pull-down), leave this function.
		if(!GetPin(MODE_CYCLE_BUTTON))
			return;
	}

	// Increment the mode
	mode++;

	if(mode > NUM_MODES)
		mode = 1;

	// Run the init light function for the mode we're on
	switch(mode)
	{
		case 1:	mode1_lights_init();
				break;

		case 2:	mode2_lights_init();
				break;

		case 3:	mode3_lights_init();
				break;

		case 4:	mode4_lights_init();
				break;

		case 5:	mode5_lights_init();
				break;

		case 6:	mode6_lights_init();
				break;

		case 7:	mode7_lights_init();
				break;

		case 8:	mode8_lights_init();
				break;
	}
}

void runISR(void)
{
	// Debounce stuff
	tTime pressed = GetTimeUS();
	tTime current = GetTimeUS();

	while((current - pressed) < DEBOUNCE_TIME)
	{
		current = GetTimeUS();

		//Check for button being let go:
		if(GetPin(START_STOP_BUTTON))
			return;
	}

	// Flip running:
	running = !running;
}

void runner(int mode)
{
	// Get state of left/right switch
	tBoolean rightSide = GetPin(LEFT_RIGHT_TOGGLE);

	// Run the mode we're currently on
	switch(mode)
	{
		case 1:	mode1(&running, rightSide);
				break;

		case 2:	mode2(&running, rightSide);
				break;

		case 3:	mode3(&running, rightSide);
				break;

		case 4:	mode4(&running, rightSide);
				break;

		case 5:	mode5(&running, rightSide);
				break;

		case 6:	mode6(&running, rightSide);
				break;

		case 7:	mode7(&running, rightSide);
				break;

		case 8:	mode8(&running, rightSide);
				break;

		default: SetRGB(rgb, 255, 128, 128);
				 break;
	}
}

void loop(void)
{
	while(1)
	{
		// While we're waiting to run..
		while(!running)
		{
			// Just runs the lightStep for the mode we're currently on:
			switch(mode)
			{
				case 1:	mode1_lights_step();
						break;

				case 2:	mode2_lights_step();
						break;

				case 3:	mode3_lights_step();
						break;

				case 4:	mode4_lights_step();
						break;

				case 5:	mode5_lights_step();
						break;

				case 6:	mode6_lights_step();
						break;

				case 7:	mode7_lights_step();
						break;

				case 8:	mode8_lights_step();
						break;

				default: defaultStepLights();
						 break;
			}

			Printf("Doing nothing... Mode is: %d | CycleButton: %d | RunButton: %d | Left/Right: %d \n", mode, GetPin(MODE_CYCLE_BUTTON), GetPin(START_STOP_BUTTON), GetPin(LEFT_RIGHT_TOGGLE));
			Wait(0.1);
		}

		// Run the choosen mode:
		runner(mode);
		// Now reset, rinse, and repeat;
		running = false;
	}
}

void main(void)
{

  InitAll();

 //  SetRGB(rgb, 0, 1, 255);
 //  // while(1)
 //  {
	//   ArmsUp(leftArm, rightArm);
	//   Printf("UP!");
	//   ArmsDown(leftArm, rightArm);
	//   Printf("Down!");
	// }

	// Printf("Down!");

	// OneColor(0x01, 0x00, 0x00);

	// uint8_t g = 0;

	// tBoolean flip = false;

 //  	while(1)
	// {
	// 	if(g == 170 || g == 0)
	// 		flip = !flip;

	// 	if(flip)
	// 		g++;
	// 	else
	// 		g--;

	// 	Wait(0.01f);
	// 	Printf("%d\n", g);
	// 	OneColor(0x00, g, 0x00);
	// }
 //  // initaLights();
 //  // setColor(3);

 //  while(1);
	void (*runFuncPtr)(void)  = &runISR;
	void (*modeFuncPtr)(void) = &incrementMode;

	// runFuncPtr  = 
	// modeFuncPtr = 

	tCallback runButton  = runFuncPtr;
	tCallback modeButton = modeFuncPtr;

	CallOnPin(runButton,  &mode, START_STOP_BUTTON);
	CallOnPin(modeButton, &mode, MODE_CYCLE_BUTTON);

	loop();// #include <stdint.h>
}