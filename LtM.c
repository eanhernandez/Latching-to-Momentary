#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void sendMomentarySignal(int momentaryDelay);
void turnOnLED(int LEDId);
void turnOffLED(int LEDId);
int isLatchPresent(int latchMonitor);
void setLatchLED(int latchState, int latchLED);

int main( int argc, const char* argv[] )
{
        int momentaryDelay = 0;					// how long in ms to charge the relay which controls the momentary circuit
        int loopDelay = 0;					// how long in ms to wait before checking for a latch

        if (argc==3)						// checking for correct number of arguments
        {
                momentaryDelay = atoi(argv[1]);
                loopDelay = atoi(argv[2]);
        }
        else
        {
                return 1;					// abort if there are no arguments
        }

                                                		// pin numbers...
        int relayControl = 0;                   		// pin id where the relay is controlled
        int powerLED = 2;                       		// pin id of the power LED
        int latchLED = 3;                       		// pin id of the latch LED
        int latchMonitor = 4;                   		// pin id where the latch is monitored

								// setting up pins...
        wiringPiSetup () ;					// mandatory wiringpi setup
	pinMode (relayControl, OUTPUT) ;			// sets relayControl pin as an output
	pinMode (powerLED, OUTPUT) ; 				// sets powerLED pin as an output
	pinMode (latchLED, OUTPUT) ;				// sets latchLED pin as an output
        pinMode (latchMonitor, INPUT) ;  			// sets latchMonitor pin as an input

	turnOnLED(powerLED);					// turn on "power" LED

	int latchState=0;                      			// tracks state of latching circuit, 1 = on and 0 = off
	latchState = isLatchPresent(latchMonitor);		// detect initial latch state

	for (;;)
	{
		if (isLatchPresent(latchMonitor)!=latchState)	// if there is change in latch: on to off, or off to on
		{						//
			latchState ^= 1;			// flip state to opposite of what it was
			setLatchLED(latchState, latchLED);	// change the latch indicator to reflect the new state
			sendMomentarySignal(momentaryDelay);    // fire momentary signal
		}
		
		delay(loopDelay) ;				// wait a bit
	}
	return 0 ;
}

void sendMomentarySignal(int momentaryDelay)			// sends the momentary signal to the privateeyepi relay board
{
        digitalWrite (0, HIGH) ;
        delay (momentaryDelay) ;
        digitalWrite (0,  LOW) ;
}
void turnOnLED(int LEDId)
{
	digitalWrite (LEDId, HIGH);
}

void turnOffLED(int LEDId)
{
	digitalWrite (LEDId, LOW);
}

int isLatchPresent(int latchMonitor)
{
	return digitalRead(latchMonitor);
}

void setLatchLED(int latchState, int latchLED)
{
	if (latchState)					// if the state shows the latch as on
	{						//
		turnOnLED(latchLED);			// turn on "latch" LED
	}						//
	else						//
	{						//
		turnOffLED(latchLED);			// or if not, turn off "latch" LED 
	}
}
