#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  wiringPiSetup () ;

  //setting up pins
  pinMode (4, INPUT) ;
  pinMode (0, OUTPUT) ;
  pinMode (2, OUTPUT) ; 
  digitalWrite (2, HIGH);
  int state=0;
  int momentaryDelay = 20;
  int loopDelay = 1;
  for (;;)
  {
	if (digitalRead(4)!=state)
	{
		if (state==0)
		{
			digitalWrite (0, HIGH) ; 
			delay (momentaryDelay) ;
			digitalWrite (0,  LOW) ; 
			state=1;
		}
		else
		{
                        digitalWrite (0, HIGH) ; 
			delay (momentaryDelay) ;
                        digitalWrite (0,  LOW) ;
			state=0;
		}
	}	
  	delay(loopDelay);
  }
  return 0 ;
}
