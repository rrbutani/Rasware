
#include <RASLib/inc/common.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>
#include <RASLib/inc/pwm.h>


static tMotor *Motors[2];
static tBoolean init1 = false;
static tBoolean init2 = false;
static tADC *adc[2];
static tPWM *arr, *gee, *bee;

static float targetWallDist = 0.73f;
static float wallDistRange  = 0.070f;
static float pollRate       = 0.125f;
// static tMotor motorRight;
// static tMotor motorLeft;


void initMotors(void) {
    if (!init1) {
      init1 = true;

      Motors[0] = InitializeServoMotor(PIN_B6, false);
      Motors[1] = InitializeServoMotor(PIN_B7, false);

    }
}
void initIRSensor(void) {
    // don't initialize this if we've already done so
    if (init2) {
        return;
    }
    init2 = true;
    // initialize 4 pins to be used for ADC input
    adc[0] = InitializeADC(PIN_E1);
    adc[1] = InitializeADC(PIN_E2);
}

void stop(void)
{
  SetMotor(Motors[0],0.0f);
  SetMotor(Motors[1],0.0f);
}

void stopFor(float duration)
{
  stop();
  Wait(duration);
}

void driveForward(void){
  SetMotor(Motors[0],0.7f);
  SetMotor(Motors[1],-0.7f);

  // Wait(pollRate);
}
void hardLeft(void){
  // SetMotor(Motors[0],-0.8f);
  // SetMotor(Motors[1],-0.5f);
  SetMotor(Motors[0], -0.8f);
  SetMotor(Motors[1], -0.8f);
}

void hardRight(void)
{
  SetMotor(Motors[0], 0.8f);
  SetMotor(Motors[1], 0.8f);
}

void right(void){
  SetMotor(Motors[0],0.85f);
  SetMotor(Motors[1],-0.25f);
}

void shiftRight(void)
{
  hardRight();
  Wait(0.13);
  stopFor(0.25);
  driveForward();
  Wait(0.17);
  stopFor(0.25);
  hardLeft();
  Wait(0.10);
  // stopFor(0.07);
  stopFor(0.25);
  driveForward();
}

void left(void){
  SetMotor(Motors[0],0.35f);
  SetMotor(Motors[1],-0.75f);
}

void setColor(int colour)
{
  SetPWM(arr, 0.0f, 0.0f);
  SetPWM(gee, 0.0f, 0.0f);
  SetPWM(bee, 0.0f, 0.0f);

  if(colour == 1) //RED
    SetPWM(arr, 0.8f, 0.0f);

  if(colour == 2) //GREEN
    SetPWM(gee, 0.8f, 0.0f);

  if(colour == 3) // Blue
    SetPWM(bee, 0.8f, 0.0f);

}


void followWall(void) {
    //adc[0]=front sensor, adc[1]=right sensor, b6=Motors[0]=left motor, b7=Motors[1]=right motor
    float frontSensor = ADCRead(adc[0]);
    float rightSensor = ADCRead(adc[1]);
    Printf("Poll!! Front: %1.3f | Right: %1.3f \n", frontSensor, rightSensor);

    if(frontSensor > targetWallDist - wallDistRange - 0.24f)
    {
      hardLeft();
      Wait(0.375f);
    }
    else if(rightSensor  >  targetWallDist + wallDistRange) //Too close to the wall?
    {
      //Turn Left!
      left();
      setColor(1); //RED
      Wait(pollRate);
    }
    else if(rightSensor  <  targetWallDist - wallDistRange) //Too far from the wall?
    {
      if(rightSensor < 0.32f)
      {
        hardRight();
        Wait(0.655f);
        driveForward();
        Wait(1.26f);
      }

      //Turn Right!
      setColor(3); //BLUE
      shiftRight(); //Magic method with waits built-in
      // Wait(pollRate);
    }
    else
    {
      //Otherwise, go straight..
      driveForward();
      setColor(2); //GREEN
      Wait(pollRate/2.0f);
    }
    // if(frontSensor<.7f && rightSensor>.7f)
    // {
    //   Printf("Onwards!\n");
    //   setColor(1); // RED
    //   driveForward();
    // }
    // else if((frontSensor>.7f && rightSensor<.7f) || (frontSensor<.7f&&rightSensor>.7f))
    // {
    //   Printf("Hard left..\n");
    //   setColor(2); // GREEN
    //   hardLeft();
    // }
    // else if(frontSensor<.7f && rightSensor<.7f)
    // {
    //   Printf("Turning right...\n");
    //   setColor(3); // BLUE
    //   right();
    // }

}

void isThatAWall(void)
{
  float frontSensor = ADCRead(adc[0]);

  if(frontSensor > 0.7f)
  {
    Printf("Wall!\n");
    setColor(2); //RED
    return;
  }

  setColor(1);
}

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    // CallEvery(blink, 0, 0.5);
    arr = InitializePWM(PIN_F1, 50.0f);
    gee = InitializePWM(PIN_F3, 50.0f);
    bee = InitializePWM(PIN_F2, 50.0f);

		// SetPWM(g, 0.5, 0.0f);
		initMotors();
    initIRSensor();
    // right();

    while (1) {
        // Runtime code can go here
        // Printf("Hello World!\n");
        // followWall();
        // isThatAWall();
        // hardRight();
        // Wait(0.5f);
        // hardLeft();
        // Wait(0.5f);
        followWall();
        // Wait(0.125f);
        // SetPWM(g, ADCRead(adc[1]), 0.0f);
    }


}
