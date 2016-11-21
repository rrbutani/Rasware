#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/linesensor.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/pwm.h>
#include <RASLib/inc/adc.h>
#include <stdbool.h>

static tLineSensor *gls;
static tMotor *Motors[3];
static tBoolean lineInit = false, motorInit = false;
static float pollRate = 0.0003f;
static float maxSpeed = 0.15f;
static tPWM *arr, *gee, *bee;
static tADC *adc[1];


void initMotors(void)
{
    if (!motorInit)
    {
      motorInit = true;

      Motors[0] = InitializeServoMotor(PIN_B6, false);
      Motors[1] = InitializeServoMotor(PIN_B7, true);
      Motors[2] = InitializeServoMotor(PIN_C4, false);
    }

    for(int i = 0; i < 3; i++)
      SetMotor(Motors[i], 0.0f);
}

void initIRSensors(void)
{
  adc[0] = InitializeADC(PIN_D2);
}
bool closeEnough(){
  float value = ADCRead(adc[0]);
  if (value>.45)
  return true;
  else
  return false;
}
void driveForward()
{

SetMotor(Motors[2],1.f);
SetMotor(Motors[1],0.6f);
SetMotor(Motors[0],-0.6f);
Wait(.3f);

SetMotor(Motors[1],.5f);
SetMotor(Motors[0],.5f);
Wait(1.35f);
SetMotor(Motors[1],.6f);
SetMotor(Motors[0],-.6f);
Wait(.5f);
SetMotor(Motors[1],1.0f);
SetMotor(Motors[0],1.0f);
Wait(3.7f);
SetMotor(Motors[1],1.0 f);
SetMotor(Motors[0],1.0f);
while(!closeEnough());

SetMotor(Motors[1],0.0f);
SetMotor(Motors[0],0.0f);

SetMotor(Motors[0],0.75f);
SetMotor(Motors[1],0.75f);
Wait(5.0f);

}

int main(void)
{
//  Printf("hi");
    initMotors();
    // initLights();
    initIRSensors();
    Printf("starting..\n");
    // float threshold;

    // threshold = getThreshold() + 0.03f;

    // alignToObject(threshold);
    // while(1){
          driveForward();
    // }

    // SetMotor(Motors[0], 0.10f);
    // SetMotor(Motors[1], 0.10f);
    // SetMotor(Motors[2], 1.00f);

}
