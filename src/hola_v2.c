#include<stdio.h>


void main()
{

char msg[100];
setvbuf(stdout,NULL,_IONBF,0);
fflush(stdout);	
while(1)
  {
    fgets(msg, 100, stdin);
    printf("Hola ");
    printf(msg);
  }

}


