#include <stdio.h>
int main (int argc, char *argv[])
#define BSIZE  64

/*
When step is BSIZE each time, dl1 miss rate is 1.56%
If step is 2*BSIZE, dl1 miss rate is 99.21%

*/
{
int a = 0;
int size=1000000*BSIZE;
char test[size];
int i =0;
for(i =0; i<size ;i++){
a=a+test[i];
i=i+BSIZE*2;
}

printf("%d",a);
}
