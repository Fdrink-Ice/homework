#include <REGX52.H>
#include "key.h"
#include "Delay.h"
#include "Nixie.h"

sbit Buzzer=P1^5;
unsigned char KeyNum;
unsigned int i;

void main()
{

	Nixie(1,0);
	while(1){
	
	KeyNum=Key();
	if(KeyNum)
	{
		for(i=0;i<100;i++)
		{
		Buzzer!=Buzzer;
	    Delay(1);
		}
	
	}Nixie(1,KeyNum);
	
	}
	

}