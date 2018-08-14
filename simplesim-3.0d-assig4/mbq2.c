#include <stdio.h>
int main (int argc, char *argv[])
#define BSIZE  64
#define NSETS  64
/*
When we run loop 2, every iteration the step is different, changing between BSIZE and BSIZE*2, the dl1 miss rate is 99.40%
If we run loop 1, the stride is the same every time. The dl1 miss rate is 0.01%

*/
{
int a = 0;
int size=100*BSIZE;
char test[size];
int i =0;
//loop1
//for(i =0; i<size ;i++){
//a=a+test[i];
//i=i+BSIZE*2;
}


//loop2
/*for (i=0;i<size;i++){
a=a+test[i];
if(i%2==0){
i=i+BSIZE;
}
else
i=i+BSIZE*2;
}*/
int vectorsize = 100;
int vector[vectorsize];
int stride =1;
int iterations=1;

for (i = 0; i < iterations; i++) {
	
	for (j = 0; j < vectorSize; j = j + stride) {
		vector[j] = vector[j] + 1;

}
printf("%d",a);
}

