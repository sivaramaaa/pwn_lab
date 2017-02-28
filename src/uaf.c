#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

struct user 
{
    int (*fp)();
    char name[10];
    char passwd[10];
};

void fetch_flag()
{
  system("/bin/sh");
}


void senddata()
{
  printf("Ur information has been Successfully saved in our Server\n");
}

void menu()
{
    printf("[1] Register\n");
    printf("[2] Report admin\n");
    printf("[3] Save Data to server\n");
    printf("[4] Delete user\n");
    printf("[5] Exit\n");
    printf("\n");
}


struct user *auth;
char  *service;

void main()
{  int choice ;
   char comments[40];
   
 while(1)
 {
   menu();
   printf("Enter your choice:");
   scanf("%d",&choice);
   switch(choice)
    {
        case 1 :
               auth = malloc(sizeof(struct user));
               printf("Enter username:\n");
               read(0,auth->name,30);
               printf("Enter password:\n");
               read(0,auth->passwd,30);
               auth->fp = senddata;            
        break;
        case 2 :
             read(0,comments,30);
             service = strdup(comments);
         break ;
        case 3:
           printf("Sending ur information to server ...\n");
           auth->fp();
        break;
        case 4:
              printf("Deleting User ...\n");
              free(auth);
          break;
        case 5:
             printf("good bye ...\n");
             exit(0);
    }
   
   
 }

}
