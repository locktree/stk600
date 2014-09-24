/*
* Wiring: FOR STK600
* PE0 -> RXD
* PE1 -> TXD
*/


#ifndef STK_UART_DRIVER_H
#define STK_UART_DRIVER_H


#define MAXLINE 81
#define CLOCK_8MHZ() CLKPR = _BV(CLKPCE); CLKPR = 0x00;
#define UART_BUFFER_SIZE 100 // size of Rx ring buffer.


typedef enum _uart_bps
{
        UART_38400,
        UART_57600,
        UART_DEFAULT,
} UART_BPS;



extern volatile uint8_t uart_rx; // Flag to indicate uart received a byte

void uart_init(UART_BPS bitrate);
void uart_putchar(char c);
char uart_getchar(int index);
void uart_putstr(char *s);

uint8_t uart_bytes_recv(void);
void uart_reset_recv(void);

/*
Global Variables:
Variables appearing in both ISR/Main are defined as 'volatile'.
*/
volatile uint8_t uart_rx; 					// Flag to indicate uart received a byte
static volatile int rxn; 					// buffer 'element' counter.
static volatile char rx[UART_BUFFER_SIZE]; 	// buffer of 'char'.








/*****************************************************
 *                  UART PUT CHAR					 *
 *****************************************************/
void uart_putchar (char c)
{
	cli();
	while ( !( UCSR0A & (1<<UDRE0)) ); 	// Wait for empty transmit buffer
		UDR0 = c; 						// Putting data into the buffer, forces transmission
	sei();
}


/*****************************************************
 *                  UART GET CHAR					 *
 *****************************************************/
char uart_getchar (int index)
{
	if (index < UART_BUFFER_SIZE) {
		return rx[index];
	}
	return 0;
}


/*****************************************************
 *                  UART PUT STRING					 *
 *****************************************************/
void uart_putstr(char *s)
{
	while(*s) uart_putchar(*s++);

}


/*****************************************************
 *                  UART INIT					 *
 *****************************************************/
void uart_init(UART_BPS bitrate)
{
	//DDRB = 0xff;
	//PORTB = 0xff;

	rxn = 0;
	uart_rx = 0;

	/* Set baud rate */
	UBRR0H = 0;
	switch (bitrate) {
		case UART_38400:
	UBRR0L = 12;
	break;
		case UART_57600:
			UBRR0L = 6;
			break;
		default:
			UBRR0L = 6;
		}

	/* Enable receiver and transmitter */
	UCSR0B = _BV(RXEN0)|_BV(TXEN0) | _BV(RXCIE0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(1<<UCSZ00) | _BV(UCSZ01);
}



uint8_t uart_bytes_recv(void)
{
	return rxn;
}



void uart_reset_recv(void)
{
	rxn = 0;
}



//Interrupt Service Routine (ISR):
ISR(USART0_RX_vect)
{
	while ( !(UCSR0A & (1<<RXC0)) );
	//PORTB = ~_BV(PINB1);
	rx[rxn] = UDR0;
	rxn = (rxn + 1) % UART_BUFFER_SIZE;
	uart_rx = 1; // notify main of receipt of data.
	//PORTB = PORTB | _BV(PINB1);
}




void test_uart()
{
	/* TESTING UART */
	char buf[MAXLINE];
	char byte;

	CLOCK_8MHZ();
	uart_init(UART_38400);
	
	snprintf(buf, MAXLINE, "Yessssssssss\n\r");	
	uart_putstr(buf);
	
	snprintf(buf, MAXLINE, "HELLO WORLD: STARTUP\n\r");
	uart_putstr(buf);

	for(;;) // Loop forever
	{
		if (uart_rx == 1) 
		{
			snprintf(buf, MAXLINE, "There is user input:\n\r");	
			uart_putstr(buf);
			byte = uart_getchar(uart_bytes_recv()-1);
			uart_rx = 0;
			_delay_ms(100);
			//uart_putchar(byte);
			uart_putchar(byte);
			
			_delay_ms(2000);
			int mynumber = (int)byte;	
			//uart_putchar(mynumber);
			snprintf(buf, MAXLINE, " + 2 will be: ");	
			uart_putstr(buf);
			
			mynumber = mynumber + 2;
			uart_putchar(mynumber);
		
			snprintf(buf, MAXLINE, "\n\r");	
			uart_putstr(buf);
		}	
	}
}

#endif





/////http://stackoverflow.com/questions/7109964/creating-your-own-header-file-in-c
