#ifndef TD_drive   /* Include guard */
#define TD_drive

#ifdef __cplusplus
extern "C" {
#endif

// Necessary Includes
	#include <RASLib/inc/servo.h>
	#include <RASLib/inc/motor.h>

// Functions:
	void DriveForward(tServo *lDrive, tServo *rDrive,float speed);
	void DriveBackward(tServo *lDrive, tServo *rDrive,float speed);
	void TurnRight(tServo *lDrive, tServo *rDrive, float speed);
	void TurnLeft(tServo *lDrive, tServo *rDrive, float speed);
	void StopDrive(tServo *lDrive, tServo *rDrive);


#ifdef __cplusplus
}
#endif

#endif // TD_drive
