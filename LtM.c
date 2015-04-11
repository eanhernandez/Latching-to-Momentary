#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void sendMomentarySignal(int momentaryDelay);

int main( int argc, const char* argv[] )
{
        int state=0;		// tracks state of latching circuit, 1 = on and 0 = off
        int momentaryDelay = 0;	// how long in ms to charge the relay which controls the momentary circuit
        int loopDelay = 0;	// how to wait in ms before checking for a latch

	// checking for correct number of arguments
        if (argc==3)
        {
                momentaryDelay = atoi(argv[1]);
                loopDelay = atoi(argv[2]);
        }
        else
        {
                return 1;	// abort if there are no arguments
        }

				//setting up pins...
        wiringPiSetup () ;	// mandatory wiringpi setup
	pinMode (4, INPUT) ;	// monitors for presence of latch
	pinMode (0, OUTPUT) ;	// controls relay on momentary circuit
	pinMode (2, OUTPUT) ; 	// powers "on" LED
	pinMode (3, OUTPUT) ;	// powers "latch" LED

	//turn on "on" light
	digitalWrite (2, HIGH);

	//detect initial latch state
	state = digitalRead(4);

	for (;;)
	{
		if (state == 1 )				// if the state shows the latch as on
		{						//
			digitalWrite (3, HIGH);			// turn on "latch" LED
		}						//
		else						//
		{						//
			digitalWrite (3, LOW);			// or if not, turn off "latch" LED 
		}

		if (digitalRead(4)!=state)			// if there is change in latch: on to off, or off to on
		{						//
			sendMomentarySignal(momentaryDelay);	// fire momentary signal
			state = state ^ 1;			// flip state to opposite of what it was
		}						//
		delay(loopDelay) ;				// wait a bit
	}
	return 0 ;
}

// sends the momentary signal to the privateeyepi relay board
// which has it's own LED to show the relay is being charged
// and thereby show that we are sending a momentary signal
void sendMomentarySignal(int momentaryDelay)
{
        digitalWrite (0, HIGH) ;
        delay (momentaryDelay) ;
        digitalWrite (0,  LOW) ;
}

