// #include <TechnicalDifficulties/inc/params.h>
#include <stdbool.h>

#include <RASLib/inc/common.h>

#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

static tMotor *Motors[2];
static tBoolean init1 = false;
static tBoolean init2 = false;
static tADC *adc[2];
float threshold = .4;
bool coneDetectedFront=false;
int numCross = 0;
bool alreadyPrinted =false;
float lastTime =0;
void initMotors(void) {
    if (!init1) {
      init1 = true;
      Motors[0] = InitializeServoMotor(PIN_B6, false);
      Motors[1] = InitializeServoMotor(PIN_B7, true);
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
void stopMotors(){
  SetMotor(Motors[0],0.0f);
  SetMotor(Motors[1],0.0f);
}
bool coneDetected(int sensor){
  float backLeft = ADCRead(adc[0]);
  float frontLeft = ADCRead(adc[1]);
  // Printf("\nbackLeft %f", backLeft);
  if (sensor==0)
  {
    if (backLeft>threshold){
      // Printf("Back sensor has seen cone!");
      return true;
    }

    else
      return false;
  }
  else{
    if(frontLeft>threshold){
      return true;

    }

    else
    return false;
  }

}
void turnRight(){
  SetMotor(Motors[0],-0.5f);
  SetMotor(Motors[1],0.5f);
  Wait(0.66f);
  stopMotors();
}
void driveForward(){
  SetMotor(Motors[0],0.29f);
  SetMotor(Motors[1],0.25f);
}
void driveSquare(void) {
  driveForward();

  Wait(3.3f);
  //Cross two cones
  for(int i = 0; i < 1; i++)
  { //Routine: One cone
    Printf("\nCROSSED %d CONES!", i);
    // if(i == 0)
    // {
      //Wait until front reaches the cone - delay is so we're safely in range..
      while(!coneDetected(1)); Wait(0.05);
      Printf("Front is at cone!");
      //Stall until front past the cone..
      while(coneDetected(1));
      Printf("Front is past cone!");
    // }
    //Wait until back reaches the cone..
    while(!coneDetected(0)); Wait(0.05);
    Printf("Back is at cone!");
    //Wait until back passes the cone..
    while(coneDetected(0));
    Printf("Back is past cone!");
  }

  turnRight();

  // if(coneDetected(1))
  // {
  //   coneDetectedFront=true;
  //    Printf("Front cone!\n");
  //   alreadyPrinted=false;
  // }
  //
  // if(coneDetected(0)&&coneDetectedFront)
  // {
  //   Printf("\n numCross %d", numCross);
  //   if(numCross==1)
  //   {
  //     Printf("\n numCrossinside %d", numCross);
  //     turnRight();
  //     coneDetectedFront=false;
  //     numCross = 0;
  //     Printf("Turned Right\n");
  //   }
  //   else{
  //     //Stall until we're past the cone.
  //     while(coneDetected(0));
  //     Wait(0.15);
  //     numCross++;
  //     // float currentTime = GetTime();
  //     // if(currentTime-lastTime > 1.0f)
  //     // {
  //     //   numCross++;
  //     //   // Printf("Incremented num Cross\n");
  //     //   // Printf("\n currenttime %f", currentTime);
  //     //   // Printf("\n lastTime %f", lastTime);
  //     //
  //     //   // lastTime =0.0f;
  //     //
  //     // }
  //     //   lastTime = currentTime;
  //   }
  //   alreadyPrinted=false;
  // }
  // else {
  //   driveForward();
  //   if(!alreadyPrinted)
  //   // Printf("Driving Forward\n");
  //   alreadyPrinted=true;
  // }
  //
  //
  // // Printf("backLeft %f", backLeft);
  // // Printf("\nfrontLeft %f\n\n",frontLeft);
  //  bool back = coneDetected(0);
  //  bool front = coneDetected(1);
  // // if (back)
  // // Printf("Back Detected\n");
  // // else
  // // Printf("Back Not Detected\n");
  // // if (front)
  // // Printf("Front Detected\n");
  // // else
  // // Printf("Front Not Detected\n");
  // // Wait(.02);
}


// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
		initMotors();
    initIRSensor();
    // while(1){driveSquare();}
    for (int i =0; i<4; i++)
    {
      driveSquare();
    }
    }
