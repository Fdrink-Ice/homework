#include <REGX52.H>

void Delay1ms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
  while(xms){
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	xms--;
  }
}

void main()
{
  int n=500;
	P2=0xFE;
	Delay1ms(n);
	P2=0xFD;
	Delay1ms(n);
	P2=0xFB;
	Delay1ms(n);
	P2=0xF7;
	Delay1ms(n);
	P2=0xEF;
	Delay1ms(n);
	P2=0xDF;
	Delay1ms(n);
	P2=0xBF;
	Delay1ms(n);
	P2=0x7F;
	Delay1ms(n);
	}