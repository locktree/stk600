enum NUMBER
{
	LED0 = 0x01,
	LED1 = 0x02,
	LED2 = 0x04,
	LED3 = 0x08,
	LED4 = 0x10,
	LED5 = 0x20,
	LED6 = 0x40,
	LED7 = 0x80,
	ALL = 0xFF
	/// access all LEDs
};

#define PortDefinition		PORTB
#define PortDirection		0xFF 	// switch all leds off


/**
* Turn the light on - ENTIRE PORTS
*/
void turnAllIoOn()
{
	DDRB = 0xFF; 		// Set Data Direction of PORTB to output
	PORTB = 0x00;		// set all low (leds on)
}


/**
* Turn the light off
*/
void turnAllIoOff()
{
	DDRB = 0xFF; 		// Set Data Direction of PORTB to output
	PORTB = 0xFF;		// set all high (leds off)
}

