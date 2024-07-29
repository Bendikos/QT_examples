#include "buzz.h"

void Buzz_Times(unsigned char times)
{
	unsigned char i = 0;
	for (i = 0; i < times; i++) {
		buzz = 0;
		delay_ms(200);
		buzz = 1;
		delay_ms(200);
	}
}
