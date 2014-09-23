#ifndef STK_IO_DRIVER_H
#define STK_IO_DRIVER_H




/*USING THE _BV MACRO  -> Bit Value  */
#define sbi(x,y) x |= _BV(y) 					//set bit - using bitwise OR operator
#define cbi(x,y) x &= ~(_BV(y)) 				//clear bit - using bitwise AND operator
#define tbi(x,y) x ^= _BV(y) 					//toggle bit - using bitwise XOR operator
#define is_high(x,y) (x & _BV(y) == _BV(y)) 	//check if the y'th bit of register 'x' is high ... test if its AND with 1 is 1


/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b,c) ((a) ^= (c<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))


/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) ((x) & (y))


#define IOPORT 			PORTB
#define PORTDIRECTION 	DDRB


typedef enum
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
} PORTNUMBER;


void turnAllIoOff();
void turnAllIoOff();
void turnSpecifiedIoOff(PORTNUMBER pn);
void turnSpecifiedIoOn(PORTNUMBER pn);
void toggleSpecifiedIO(PORTNUMBER pn);
void ledDemo();




/*****************************************************
 * THIS FUNCTION CONTAINS SOME LED DEMONSTRATIONS    *
 *****************************************************/
void ledDemo() 
{
	/* specify a DELAY time */
	const int DELAY = 		250;
	const int LONG_DELAY =	3000;
	


	/*****************************************
	 * DEMO 1 - TURN ON AND TURN OF ALL LEDS *
	 *****************************************/ 
	int iterator = 0;
	for (iterator = 0 ; iterator < 5 ; iterator++)
	{
		turnAllIoOn();
		_delay_ms(DELAY);
		turnAllIoOff();
		_delay_ms(DELAY);
	}
	_delay_ms(LONG_DELAY);

	/*********************************
	 * DEMO 2 - TURN SPECIFIED IO ON *
	 *********************************/
	turnAllIoOff();
	_delay_ms(DELAY);
	turnSpecifiedIoOn(LED2);
	_delay_ms(DELAY);
	turnSpecifiedIoOn(LED3);
	_delay_ms(DELAY);
	turnSpecifiedIoOn(LED4);
	_delay_ms(DELAY);
	turnSpecifiedIoOn(LED5);
	_delay_ms(DELAY);
	_delay_ms(LONG_DELAY);


	/**********************************
	 * DEMO 3 - TURN SPECIFIED IO OFF *
	 **********************************/
	turnAllIoOn();
	_delay_ms(DELAY);
	turnSpecifiedIoOff(LED2);
	_delay_ms(DELAY);
	turnSpecifiedIoOff(LED3);
	_delay_ms(DELAY);
	turnSpecifiedIoOff(LED4);
	_delay_ms(DELAY);
	turnSpecifiedIoOff(LED5);
	_delay_ms(DELAY);
	_delay_ms(LONG_DELAY);


	/********************************
	 * DEMO 4 - USING THE BV MACRO  *
	 ********************************/
	turnAllIoOff();
	_delay_ms(DELAY);
	tbi(PORTB,PB4);   		//here the toggling takes place
	_delay_ms(LONG_DELAY);
	
	
	/********************************
	 * DEMO 5 - Toggle Specified IO *
	 ********************************/
	 turnAllIoOff();
	 _delay_ms(1000);
	 tbi(PORTB,PB2);   		//here the toggling takes place
	 tbi(PORTB,PB3);   		//here the toggling takes place
	 tbi(PORTB,PB4);   		//here the toggling takes place
	 tbi(PORTB,PB5);   		//here the toggling takes place
	 toggleSpecifiedIO(LED4);
	 _delay_ms(1000);
	 toggleSpecifiedIO(LED4);
	 _delay_ms(1000);
	 toggleSpecifiedIO(LED4);
	 _delay_ms(1000);
	 toggleSpecifiedIO(LED4);
	 _delay_ms(1000);
	 toggleSpecifiedIO(LED4);
	 _delay_ms(1000);

	 
	 /*******************************
	  * DEMO 7 - BINARY COUNT *
	  ******************************/

	 binary_count();
	 
	 testSpecifiedButton(0x08);		//when pressing the 4th(SW3) button...
}




/* TURN ON ENTIRE PORT */
void turnAllIoOn()
{
	PORTDIRECTION = 0xFF; 		// Set Data Direction of PORTB to output
	IOPORT = 0x00;				// set all low (leds on)
}


/* TURN OFF ENTIRE PORT */
void turnAllIoOff()
{
	PORTDIRECTION = 0xFF; 		// Set Data Direction of PORTB to output
	IOPORT = 0xFF;				// set all high (leds off)
}


void turnSpecifiedIoOn(PORTNUMBER pn)
{
	PORTDIRECTION = 0xFF;			// Set Data Direction of PORTB to output	
	int number1 = ~IOPORT;			//current value
	int number2 = pn;				//value to add
	int number3 = number1 | number2;
	IOPORT = ~number3;
}

void turnSpecifiedIoOff(PORTNUMBER pn)
{
	PORTDIRECTION = 0xFF;			// Set Data Direction of PORTB to output
	int number1 = IOPORT;			//current value
	int number2 = pn;				//value to add
	int number3 = number1 | number2;
	IOPORT = number3;
}


void toggleSpecifiedIO(PORTNUMBER pn)
{
	PORTDIRECTION = 0xFF;
	int number3 = BIT_FLIP(IOPORT,~pn,pn);
	IOPORT = number3;
	
}


/* Binary count */
void binary_count()
{
	DDRB = 0xFF; 				// Set Data Direction of PORTB to output
	PORTB = 0xFF; 				// Set all pins to 1 (LEDs are active low)
	unsigned char a = 0x00;		//our counter
	
	while(a <= 0xFF)
	{
		PORTB = ~a;
		_delay_ms(50);
		if(a == 0xFF)
		{
			break;
			a = 0;
		}
		a = a + 1;
	}
	_delay_ms(250);
}




/* 	WILL RESPONSE ON A SPECIFIED BUTTON */
void testSpecifiedButton(int ButtonNumber )
{
	unsigned char pressedButton = 0;
	for(;;)
	{  
		pressedButton = ~PIND;
		if (pressedButton == ButtonNumber)  
		{
			binary_count();
		}
	}
}




#endif

