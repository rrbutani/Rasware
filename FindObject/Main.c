#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/linesensor.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/pwm.h>
#include <RASLib/inc/adc.h>

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
  adc[0] = InitializeADC(PIN_E1);
}

float getThreshold(void)
{
  SetMotor(Motors[0], 0.15f);
  SetMotor(Motors[1], -0.15f);

  float lowest = 1.0f, currentDist;

  tTime start = GetTime();

  while(GetTime() - start < 7.5f)
  {
    currentDist = ADCRead(adc[0]);

    if(currentDist < lowest)
      lowest = currentDist;

    Printf("Current: %f | Lowest: %f\n", currentDist, lowest);
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

  float currentDist = 1.0f;

  while(currentDist > threshold)
  { // Stop when we reach the object?\

    currentDist = ADCRead(adc[0]);
    Printf("Current: %f, | Threshold: %d\n", currentDist, threshold);
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

// void hardRight(void)
// {
//   SetMotor(Motors[0], 0.8f);
//   SetMotor(Motors[1], 0.8f);
// }

// void driveForward(void){
//   SetMotor(Motors[0],0.7f);
//   SetMotor(Motors[1],-0.7f);

//   // Wait(pollRate);
// }
// void driveBackward(void){
//   SetMotor(Motors[0],-0.7f);
//   SetMotor(Motors[1],+0.7f);

//   // Wait(pollRate);
// }
// float min(float a, float b)
// {
//   return a > b ? b : a;
// }

// float max(float a, float b)
// {
//   return a < b ? b : a;
// }

// void setMotors(float rate, float speed)
// {
//     // Printf("%f ", rate);
//     SetMotor(Motors[0], max((maxSpeed * speed) - rate, 0.07f));
//     SetMotor(Motors[1], -1.0f * max(((maxSpeed * speed) + rate) * 1.0f, 0.07f));
// }

int main(void)
{
    initMotors();
    // initLights();
    initIRSensors();

    // float line[8];
    // float rates[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
    // // float slowdown[8] = {-0.1f, -0.05f, -0.01f, 0.0f, 0.0f, -0.01f, -0.05f, -0.1f};
    // float rate;
    // , speed, sumSlowdown;
    // int numBlack;
    Printf("starting..\n");
    float threshold; 

    threshold = getThreshold() + 0.03;

    alignToObject(threshold);

    // SetMotor(Motors[0], 0.10f);
    // SetMotor(Motors[1], 0.10f);
    // SetMotor(Motors[2], 1.00f);

    // while(1)
    {
      // rate = 0.0f;
      // speed = 1.0f;
      // numBlack = 0;

      // LineSensorReadArray(gls, line);

      // for(int i = 0; i < 8; i++)
      // {
      //   float sensorValue = (line[i] > .5f) ? 1.0f : 0.0f;
      //   float indivRate   = sensorValue * rates[i];
      //   // float indivSlow   = sensorValue * slowdown[i];

      //   rate += indivRate;
      //   // sumSlowdown += indivSlow;

      //   // if(sensorValue >= 1.0f)
      //   //     numBlack++;

      //   // Printf("%.2f ,", sensorValue);
      // }

      // if(line[0] >= 1.0f)
      // {
      //   while(line[2] < 0.35f)
      //   {
      //     LineSensorReadArray(gls, line);
      //     SetMotor(Motors[0], 0.95f);
      //     SetMotor(Motors[1], -0.2f);
      //     // Wait(2.0f);
      //     // hardRight();

      //   }
      //   driveForward();
      //   // hardRight();
      //   // Wait(0.35f);
      //   // driveForward();
      //   // Wait(0.12f);

      //   // driveForward();
      //   // Wait(0.13f);
      // }

      // rate /= numBlack;
      // sumSlowdown /= max(numBlack * 1.0f, 1.0f);

      // speed += sumSlowdown;

      // if(rate > 0)
      // {
      //   // setColor(1);
      //   //turn right
      //   SetMotor(Motors[0], 0);
      //   SetMotor(Motors[1], -0.35f);
      // }
      // else if(rate < 0)
      // {
      //   // setColor(3);
      //   //turn left        
      //   SetMotor(Motors[0], 0.35f);
      //   SetMotor(Motors[1], 0);
      // }
      // else
      // {
      //   // setColor(2);
      //   //turn right
      //   SetMotor(Motors[0], 0.2f);
      //   SetMotor(Motors[1], -0.2f);
      // }

      // Printf(" --> %.2f for %d black readings..\n", rate, numBlack);

      // setMotors(rate, 1.0f);

      // Wait(pollRate);
    }
    // while(1)
    //   setMotors(-0.2f);
}

// void gpioLineSensorDemo(void) {
//     Printf("Press any key to quit\n");
//
//     // loop as long as the user doesn't press a key
//     while (!KeyWasPressed()) {
//         int i;
//         float line[8];
//
//         // put the values of the line sensor into the 'line' array
//         LineSensorReadArray(gls, line);
//         Printf("Line Sensor: [");
//
//         for (i = 0; i < 8; i++) {
//             Printf("%.2f ", line[i]);
//         }
//
//         Printf("\b]        \r");
//     }
//
//     Printf("\n");
// }


//
// #include <RASLib/inc/common.h>
// #include <RASLib/inc/motor.h>
// #include <RASLib/inc/time.h>
// #include <RASLib/inc/adc.h>
// #include <RASLib/inc/pwm.h>
// #include <RASLib/inc/linesensor.h>
//
//
// static tMotor *Motors[2];
// static tBoolean init1 = false;
// static tBoolean init2 = false;
// static tADC *adc[2];
// static tPWM *arr, *gee, *bee;
//
// static float lineThreshold;
//
// static float pollRate       = 0.125f;
//
//
// void initMotors(void) {
//     if (!init1) {
//       init1 = true;
//
//       Motors[0] = InitializeServoMotor(PIN_B6, false);
//       Motors[1] = InitializeServoMotor(PIN_B7, false);
//
//     }
// }
// void initGPIOLineSensor(void) {
//     // don't initialize this if we've already done so
//     if (init2) {
//         return;
//     }
//
//     init2 = true;
//
//     // use 8 I/O pins to initialize a GPIO line sensor
//     gls = InitializeGPIOLineSensor(
//       PIN_B3,
//       PIN_C4,
//       PIN_C5,
//       PIN_C6,
//       PIN_C7,
//       PIN_D6,
//       PIN_D7,
//       PIN_F4
//       );
// }
//
// void stop(void)
// {
//   SetMotor(Motors[0],0.0f);
//   SetMotor(Motors[1],0.0f);
// }
//
// void stopFor(float duration)
// {
//   stop();
//   Wait(duration);
// }
//
// void driveForward(void){
//   SetMotor(Motors[0],0.7f);
//   SetMotor(Motors[1],-0.7f);
//
//   // Wait(pollRate);
// }
// void hardLeft(void){
//   // SetMotor(Motors[0],-0.8f);
//   // SetMotor(Motors[1],-0.5f);
//   SetMotor(Motors[0], -0.8f);
//   SetMotor(Motors[1], -0.8f);
// }
//
// void hardRight(void)
// {
//   SetMotor(Motors[0], 0.8f);
//   SetMotor(Motors[1], 0.8f);
// }
//
// void right(void){
//   SetMotor(Motors[0],0.85f);
//   SetMotor(Motors[1],-0.25f);
// }
//
// void left(void){
//   SetMotor(Motors[0],0.35f);
//   SetMotor(Motors[1],-0.75f);
// }
//
// void setColor(int colour)
// {
//   SetPWM(arr, 0.0f, 0.0f);
//   SetPWM(gee, 0.0f, 0.0f);
//   SetPWM(bee, 0.0f, 0.0f);
//
//   if(colour == 1) //RED
//     SetPWM(arr, 0.8f, 0.0f);
//
//   if(colour == 2) //GREEN
//     SetPWM(gee, 0.8f, 0.0f);
//
//   if(colour == 3) // Blue
//     SetPWM(bee, 0.8f, 0.0f);
//
// }
//
// bool isHigh(float num)
// {
//   if (num>lineThreshold)
//    return;
// }
//
// void followLine()
// {
//   float line[8];
//   LineSensorReadArray(gls, line);
//   float leftSensor = line[2];
//   float rightSensor = line[6];
//   float midSensor = line[4];
//
//   if (isHigh(midSensor)&&!isHigh(leftSensor)&&!isHigh(rightSensor))
//   {
//     driveForward();
//   }
//   else if(isHigh())
//
// }
//
// // The 'main' function is the entry point of the program
// int main(void) {
//     // Initialization code can go here
//     // CallEvery(blink, 0, 0.5);
//     arr = InitializePWM(PIN_F1, 50.0f);
//     gee = InitializePWM(PIN_F3, 50.0f);
//     bee = InitializePWM(PIN_F2, 50.0f);
//
// 		// SetPWM(g, 0.5, 0.0f);
// 		initMotors();
//     initIRSensor();
//     // right();
//
//     while (1) {
//         // Runtime code can go here
//         // Printf("Hello World!\n");
//         // followWall();
//         // isThatAWall();
//         // hardRight();
//         // Wait(0.5f);
//         // hardLeft();
//         // Wait(0.5f);
//         followWall();
//         // Wait(0.125f);
//         // SetPWM(g, ADCRead(adc[1]), 0.0f);
//     }
//
//
// }
