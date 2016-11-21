#include <rgbled.h>

#include <stdint.h>			 //For uint8_t type

#include <RASLib/inc/pwm.h>  //For controlling the LED
#include <RASLib/inc/gpio.h> //For tPin type

#include <TechnicalDifficulties/inc/shared.h>

// Struct for an RGB LED:
struct RGB
{
	tPWM *R, *G, *B;
};

// Buffer for RGB structs (stack memory allocation)
static tRGB rgbBuffer[RGB_MODULE_COUNT];

static int usedRGBModules = 0;

// Functions for an RGB LED Module:

void SetRGB(tRGB *rgb, uint8_t r, uint8_t g, uint8_t b)
{
	SetPWM(rgb->R, (r/255.0f), 0.0f);
	SetPWM(rgb->G, (g/255.0f), 0.0f);
	SetPWM(rgb->B, (b/255.0f), 0.0f);
}

void off(tRGB *rgb)
{
	SetRGB(rgb, 0.0f, 0.0f, 0.0f);
}

tRGB *InitializeRGB(tPin r, tPin g, tPin b)
{
	//Check if we're out of allocated modules; don't return though
	if(usedRGBModules == RGB_MODULE_COUNT)
		throw_error();

	//Grab next allocated module and increment used modules
	tRGB *rgb = &rgbBuffer[usedRGBModules++];

	rgb->R = InitializePWM(r, 50.0f);
	rgb->G = InitializePWM(g, 50.0f);
	rgb->B = InitializePWM(b, 50.0f);


	SetPWM(rgb->R, 1.0f, 0.0f);
	SetPWM(rgb->G, 1.0f, 0.0f);
	SetPWM(rgb->B, 1.0f, 0.0f);

	off(rgb);

	return rgb;
}