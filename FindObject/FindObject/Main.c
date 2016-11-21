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
  adc[0] = InitializeADC(PIN_E2);
}

float getThreshold(void)
{
  Printf("getting threshold");
  SetMotor(Motors[0], 0.15f);
  SetMotor(Motors[1], -0.15f);

  float lowest = 1.0f, currentDist;

  tTime start = GetTime();

  while(GetTime() - start < 7.5f)
  {
    currentDist = ADCRead(adc[0]);

    if(currentDist < lowest)
      lowest = currentDist;

//    Printf("Current: %f | Lowest: %f\n", currentDist, lowest);
  }

  return lowest;

  // while(1)
  // {
  //   // SetMotor(Motors[0], 0.1f);
  //   // SetMotor(Motors[1], -0.1f);

  //   Printf("Dist Sensor: %f\n", ADCRead(adc[0]));
  // }
}

void alignToObject(float threshold)
{
  //Spin!!
  SetMotor(Motors[0], 0.10f);
  SetMotor(Motors[1], -0.10f);
  // Printf("Hello everybody!");
  float currentDist = 1.0f;

  while(currentDist > threshold)
  { // Stop when we reach the object?\

    currentDist = ADCRead(adc[0]);
  //  Printf("Current: %f, | Threshold: %d\n", currentDist, threshold);
  }

  SetMotor(Motors[0], 0.0f);
  SetMotor(Motors[1], 0.0f);

  Wait(0.5f);

  SetMotor(Motors[0], -0.10f);
  SetMotor(Motors[1], 0.10f);

  float startTime = GetTime();

  while(GetTime() - startTime < 0.80);

  SetMotor(Motors[0], 0.0f);
  SetMotor(Motors[1], 0.0f);



}
bool closeEnough()
{
  Printf("\nDistance is %f",ADCRead(adc[0]));
  if (ADCRead(adc[0])>.85f)
  {
    return true;
    Printf("\ncloseEnough");
  }
    return false;

}

void driveToObject()
{
  Printf("\nDriving to object!");
  SetMotor(Motors[0],.17f);
  SetMotor(Motors[1],.15f);
  while(!closeEnough());
  SetMotor(Motors[0],-0.15f);
  SetMotor(Motors[1],0.15f);
  Wait(.5f);
  SetMotor(Motors[0],0.0f);
  SetMotor(Motors[1],0.0f);

}

int main(void)
{
//  Printf("hi");
    initMotors();
    // initLights();
    initIRSensors();
    Printf("starting..\n");
    float threshold;

    threshold = getThreshold() + 0.03f;

    alignToObject(threshold);
    driveToObject();
    // SetMotor(Motors[0], 0.10f);
    // SetMotor(Motors[1], 0.10f);
    // SetMotor(Motors[2], 1.00f);

}
