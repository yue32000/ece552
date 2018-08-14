#include <stdio.h>
/*
This microbenchmark is designed for both question 1 and question 2. We included 1 cycle stall and 2 cycles stall conditions to validate sim-safe.



*/
int main (int argc, char *argv[])
  

  {
	 int i=0;
		
	int a=1;
	int b=1;
	int c=0;
	int d=1;
	int e=1;
	int f=1;
	int g=0;	
	/*The following loop has three RAW dependency

	$L17:
		addu	$7,$5,$6
		addu	$6,$5,$7
		addu	$3,$3,1
		slt		$2,$8,$3
		beq		$2,$0,$L17
	*/	

	 for (i=0;i<1000000;i++)
		{
			c=a+b;
			b=a+c;
		}
	
	/*The following loop has three RAW dependency
	$L22:
		addu	$8,$10,$9
		addu	$4,$4,1     //only difference with loop 1. have an instruction between two RAW dependency instruciton
		addu	$9,$10,$8
		addu	$5,$5,1
		addu	$3,$3,1
		slt		$2,$11,$3
		beq		$2,$0,$L22
	*/
	for(i=0;i<500000;i++) 
	 {
		 g=e+f;
		 d=d+1;
		 f=e+g;
		 a=a+1;
	 }
	/*The following loop has four RAW dependency. Designed to test LW instruction in question2
	$L27:
	 #APP
		lw $2 , 0($sp)
		addu $5,$2,$2
	 #NO_APP
		addu	$4,$4,1
	 #APP
		lw $2 , 0($sp)
		nop
		addu $5,$2,$2
	 #NO_APP
		addu	$3,$3,1
		slt	$2,$11,$3
		beq	$2,$0,$L27

	*/
	for(i=0;i<2000000;i++)
	{

		asm("lw $2 , 0($sp)");
		asm("addu $5,$2,$2");
		d=d+1;
		asm("lw $2 , 0($sp)");
		asm("nop");
		asm("addu $5,$2,$2");
	}
	printf("% d , %d , %d,%d,%d,%d,%d",a,b,c,d,e,f,g);
return 0;

  }
