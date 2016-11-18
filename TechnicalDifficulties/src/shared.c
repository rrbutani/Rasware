#include <shared.h>

#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

static tBoolean blink_on = false;

void blink(void)
{
    SetPin(PIN_F1, blink_on);
    blink_on = !blink_on;
}

void throw_error(void)
{
	CallEvery(blink, 0, 0.2);
}