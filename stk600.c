#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdio.h> 
#include <avr/interrupt.h> // ISR handling.
#include <stdint.h>
#include <stdio.h>

#include "IODriverStk600.h"



/* STK600 CONFIGURATION:
 * -PORT B -> SWITCHES
 * -PORT D -> LEDS
 * -PROGRAMMING: UBUNTU: ISP
 *               WINDOWS:JTAG
 */




int main(void)
{
	ledDemo();
	return 0;
}




