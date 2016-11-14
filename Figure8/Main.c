
#include <RASLib/inc/common.h>

#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>

static tMotor *Motors[2];
static tBoolean initialized = false;
// static tMotor motorRight;
// static tMotor motorLeft;


void initMotors(void) {
    if (!initialized) {
      initialized = true;

      Motors[0] = InitializeServoMotor(PIN_B6, false);
      Motors[1] = InitializeServoMotor(PIN_B7, false);

    }
}
void driveForward(void) {

  // motorRight = Motors[1];
  // motorLeft = Motors[0];
  // SetMotor(Motors[1],.5);//increasing magnitude makes it turn left
  // SetMotor(Motors[0],.5);
  // Printf("moving forward");
  // Wait(0.6);
  // return;
  SetMotor(Motors[0],0);
  SetMotor(Motors[1],0);

}


// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    //CallEvery(blink, 0, 0.5);
		initMotors();
    // while (1) {
    //     // Runtime code can go here
    //     // Printf("Hello World!\n");
        driveForward();
    //     return;
    // }


}
