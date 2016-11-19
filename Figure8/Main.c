// #include <TechnicalDifficulties/inc/params.h>


#include <RASLib/inc/common.h>

#include <RASLib/inc/motor.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

static tMotor *Motors[2];
static tBoolean init1 = false;
static tBoolean init2 = false;
// static tMotor motorRight;
// static tMotor motorLeft;
static tADC *adc[2];

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
void driveForward(void) {


  float backLeft = ADCRead(adc[0]);
  float frontLeft = ADCRead(adc[1]);
  Printf("frontLeft %f", frontLeft);
  Printf("\nfrontRight %f\n\n",frontRight);
  // SetMotor(Motors[0],0.2);
  // SetMotor(Motors[1],0.12);
  Wait(.1*2);
  // SetMotor(Motors[0],0.14);
  // SetMotor(Motors[1],0.18);
  // return;

}
void stopMotors(void){
  SetMotor(Motors[0],0);
  SetMotor(Motors[1],0);
}

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    //CallEvery(blink, 0, 0.5);
		initMotors();
    initIRSensor();
    while(1){driveForward();}
    // while (1) {
    //     // Runtime code can go here
    //     // Printf("Hello World!\n");
        // driveForward();
        // stopMotors();
        // return;
    //     return;
    // }


}
