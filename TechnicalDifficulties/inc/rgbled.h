#ifndef TD_RGBLED   /* Include guard */
#define TD_RGBLED

#ifdef __cplusplus
extern "C" {
#endif

// Max number of RGB LED Modules, for stack memory allocation purposes
// Currently set arbitarily to 4, but really it's physically possible
// to have as many as 14 on the LM4F120XL (42 GPIO/3 = 14)
// And that's without reusing any pins for different modules...
// This is fine for now, though.
#define RGB_MODULE_COUNT 4

// Necessary includes
#include <stdint.h>			 //For uint8_t type
#include <RASLib/inc/gpio.h> //For tPin type

// Typedef RGB
typedef struct RGB tRGB;

// Functions:
tRGB *InitializeRGB(tPin r, tPin g, tPin b);
void SetRGB(tRGB *rgb, uint8_t r, uint8_t g, uint8_t b);
void off(tRGB *rgb);


#ifdef __cplusplus
}
#endif

#endif // TD_RGBLED