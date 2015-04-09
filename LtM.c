#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (4, INPUT) ;
  pinMode (0, OUTPUT) ;
  pinMode (2, OUTPUT) ; 
  digitalWrite (2, HIGH);
  int state=0;
  for (;;)
  {
	if (digitalRead(4)!=state)
	{
		if (state==0)
		{
			digitalWrite (0, HIGH) ; delay (250) ;
			digitalWrite (0,  LOW) ; 
	                //printf("latch on --> flip momentary \n");
        	        //fflush(stdout);
			state=1;
		}
		else
		{
                        digitalWrite (0, HIGH) ; delay (250) ;
                        digitalWrite (0,  LOW) ;


                        //printf("latch off --> flip momentary \n");
                        //fflush(stdout);
			state=0;
		}
	}	
  	delay(1);
  }
  return 0 ;
}


