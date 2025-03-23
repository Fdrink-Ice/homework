#include <REGX52.H>
#include "Delay.h"
char NUM[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
void Nixie(char cont,char num ){
char N,M,T;
   
	 switch(cont){
	 case 1:N=1;M=1;T=1;break;
	 case 2:N=1;M=1;T=0;break;
	 case 3:N=1;M=0;T=1;break;
	 case 4:N=1;M=0;T=0;break;
	 case 5:N=0;M=1;T=1;break;
	 case 6:N=0;M=1;T=0;break;
	 case 7:N=0;M=0;T=1;break;
	 case 8:N=0;M=0;T=0;break;
}
	 P2_4=N;
	 P2_3=M;
	 P2_2=T;
	 P0=NUM[num];
	 Delay(1);
	 P0=0X00;
	 }