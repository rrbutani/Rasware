#ifndef TD_RGBLED   /* Include guard */
#define TD_RGBLED

#ifdef __cplusplus
extern "C" {
#endif

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