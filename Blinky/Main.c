#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

// Blink the LED to show we're on
tBoolean blink_on = true;
int sleepTime = 250;

void blink2(void)
{
	Printf(GetPin(PIN_F0) ? "1" : "0");
	SetPin(PIN_F3, blink_on);
	blink_on = !blink_on;

	Wait(0.3);
	if (GetPin(PIN_F0))
		Wait(0.3);
}


// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    //CallEvery(blink, 0, 0.5);
    
    while (1) {
        // Runtime code can go here
        // Printf("Hello World!\n");
        blink2();
    }
}
