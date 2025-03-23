#include <REGX52.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char KeyNumber =0;
	
	if(P2_1==0){Delay(20);while(P2_1==0);Delay(20);KeyNumber=1;}
    if(P2_0==0){Delay(20);while(P2_0==0);Delay(20);KeyNumber=2;}
    if(P2_2==0){Delay(20);while(P2_2==0);Delay(20);KeyNumber=3;}
    if(P2_3==0){Delay(20);while(P2_3==0);Delay(20);KeyNumber=4;}

	return KeyNumber;

}	