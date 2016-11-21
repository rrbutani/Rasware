#ifndef TD_EVOM   /* Include guard */
#define TD_EVOM

#ifdef __cplusplus
extern "C" {
#endif

// Necessary Includes
	#include <RASLib/inc/servo.h>
	#include <RASLib/inc/motor.h>

// Functions:
	void ArmsUp(tServo *lArm, tServo *rArm);
	void ArmsDown(tServo *lArm, tServo *rArm);
	void Intake(tMotor *intake);
	void Extake(tMotor *intake);
	void StopIntake(tMotor *intake);


#ifdef __cplusplus
}
#endif

#endif // TD_EVOM
