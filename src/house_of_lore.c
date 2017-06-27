#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void evil_func(void)
{
  printf("\nThis is an evil function. You become a cool hacker if you are able to execute it.\n");
}

void func1(void)
{
  char *lb1, *lb2;

  unsigned int a = 0xffffd1bc;
  unsigned int b = 0xffffd1c4;
  unsigned int c = 0x804c400;

 // printf("a=%p,b=%p,c=%p",&a,&b,&c);

  lb1 = (char *) malloc(128);
  printf("LB1 -> [ %p ]", lb1);
  lb2 = (char *) malloc(128);
  printf("\nLB2 -> [ %p ]", lb2);

  strcpy(lb1, "Which is your favourite hobby? ");
  printf("\n%s", lb1);
  fgets(lb2, 128, stdin);
}

int main(int argc, char *argv[])
{
  char *buff1, *buff2, *buff3;

  printf("[+] argv =%s",argv[1]);

  malloc(4056);
  buff1 = (char *) malloc(16);
  printf("\nBuff1 -> [ %p ]", buff1);
  buff2 = (char *) malloc(128);
  printf("\nBuff2 -> [ %p ]", buff2);
  buff3 = (char *) malloc(256);
  printf("\nBuff3 -> [ %p ]\n", buff3);

  free(buff2);

  printf("\nBuff4 -> [ %p ]\n", malloc(1423));

  strcpy(buff1, argv[1]);

  func1();

  return 0;
}
