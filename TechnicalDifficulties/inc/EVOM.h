#ifndef TD_EVOM   /* Include guard */
#define TD_EVOM

#ifdef __cplusplus
extern "C" {
#endif

// Necessary Includes
	#include <RASLib/inc/servo.h>

// Functions:
	void ArmsUp(tServo *lArm, tServo *rArm);
	void ArmsDown(tServo *lArm, tServo *rArm);


#ifdef __cplusplus
}
#endif

#endif // TD_EVOM