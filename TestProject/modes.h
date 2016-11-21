#ifndef TD_MODES
#define TD_MODES

#ifdef __cplusplus
extern "C" {
#endif

#include <RASLib/inc/common.h>

#define NUM_MODES 8

// Mode Methods:
void modeOneInitLights(void);
void modeOneStepLights(void);
void ModeOne(tBoolean *running, tBoolean rightSide);

void modeTwoInitLights(void);
void modeTwoStepLights(void);
void ModeTwo(tBoolean *running, tBoolean rightSide);

void modeThreeInitLights(void);
void modeThreeStepLights(void);
void ModeThree(tBoolean *running, tBoolean rightSide);

void modeFourInitLights(void);
void modeFourStepLights(void);
void ModeFour(tBoolean *running, tBoolean rightSide);

void modeFiveInitLights(void);
void modeFiveStepLights(void);
void ModeFive(tBoolean *running, tBoolean rightSide);

void modeSixInitLights(void);
void modeSixStepLights(void);
void ModeSix(tBoolean *running, tBoolean rightSide);

void modeSevenInitLights(void);
void modeSevenStepLights(void);
void ModeSeven(tBoolean *running, tBoolean rightSide);

void modeEightInitLights(void);
void modeEightStepLights(void);
void ModeEight(tBoolean *running, tBoolean rightSide);


// Mode mappings
#define mode1(R, LR) ModeOne(R, LR)
#define mode2(R, LR) ModeTwo(R, LR)
#define mode3(R, LR) ModeThree(R, LR)
#define mode4(R, LR) ModeFour(R, LR)
#define mode5(R, LR) ModeFive(R, LR)
#define mode6(R, LR) ModeSix(R, LR)
#define mode7(R, LR) ModeSeven(R, LR)
#define mode8(R, LR) ModeEight(R, LR)

#define mode1_lights_init() modeOneInitLights()
#define mode2_lights_init() modeTwoInitLights()
#define mode3_lights_init() modeThreeInitLights()
#define mode4_lights_init() modeFourInitLights()
#define mode5_lights_init() modeFiveInitLights()
#define mode6_lights_init() modeSixInitLights()
#define mode7_lights_init() modeSevenInitLights()
#define mode8_lights_init() modeEightInitLights()

#define mode1_lights_step() modeOneStepLights()
#define mode2_lights_step() modeTwoStepLights()
#define mode3_lights_step() modeThreeStepLights()
#define mode4_lights_step() modeFourStepLights()
#define mode5_lights_step() modeFiveStepLights()
#define mode6_lights_step() modeSixStepLights()
#define mode7_lights_step() modeSevenStepLights()
#define mode8_lights_step() modeEightStepLights()

#ifdef __cplusplus
}
#endif

#endif // _TD_MODES