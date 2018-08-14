#include <stdio.h>
int main (int argc, char *argv[])
#define BSIZE  64

/*
The configuation of the cache is 64 bytes per block.

If we run only loop 1, the stride is the same every time, it only uses the stride prefetcher part. Thus,the dl1 miss rate is 0.01%
If we only run loop 2 for one time, in loop2, it cannot use stride prefetcher beacuse every iteration the stride is different and the dl1 miss rate is 67.49%. The first time we run loop 2 is when correaltion prefetcher set up its tag and address. When we increse the number repetition of loop2, dl1 miss rate drops because the use of correaltion prefetcher. If we run 10 times of loop 2, dl1 miss rate is 32.33%.
*/
{
int a = 0;
int size=1000000*BSIZE;
char test[size];
int i =0;
int j=0;
//loop1
/*for(i =0; i<size ;){
a=a+test[i];
i=i+BSIZE*2;
}*/


//loop2

i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}


//repeats of loop2

i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}	
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}	
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}	
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}			
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}
i=0;
		for (j=0;j<8192&&i<size;j++){
			a=a+test[i];	
			if(j%2==0){
				i=i+BSIZE+1;
				}
			else
				i=i+BSIZE*2+1;
			}
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}	
i=0;
	for (j=0;j<8192&&i<size;j++){
		a=a+test[i];
		if(j%2==0){
			i=i+BSIZE+1;
		}
		else
			i=i+BSIZE*2+1;
		}	
printf("%d",a);
}
