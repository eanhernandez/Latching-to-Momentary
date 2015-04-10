#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void sendMomentarySignal(int momentaryDelay);

int main( int argc, const char* argv[] )
{
        int state=0;
        int momentaryDelay = 0;
        int loopDelay = 0;

	// checking for correct number of arguments
        if (argc==3)
        {
                momentaryDelay = atoi(argv[1]);
                loopDelay = atoi(argv[2]);
        }
        else
        {
                return 1;
        }

	//setting up pins
        wiringPiSetup () ;
	pinMode (4, INPUT) ;
	pinMode (0, OUTPUT) ;
	pinMode (2, OUTPUT) ; 
	pinMode (3, OUTPUT) ;

	//turn on "on" light
	digitalWrite (2, HIGH);

	//detect initial latch state
	state = digitalRead(4);

	for (;;)
	{
		if (state == 1 )
		{
			digitalWrite (3, HIGH);
		}
		else
		{
			digitalWrite (3, LOW);
		}


		if (digitalRead(4)!=state)
		{
			sendMomentarySignal(momentaryDelay);
			state = state ^ 1;
		}	
		delay(loopDelay) ;
	}
	return 0 ;
}

void sendMomentarySignal(int momentaryDelay)
{
        digitalWrite (0, HIGH) ;
        delay (momentaryDelay) ;
        digitalWrite (0,  LOW) ;
}

