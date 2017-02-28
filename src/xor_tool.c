#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

void encrypt()
{
    char key = '\x02';
    int i ;
    char *line ;
    char buff[50];
    printf("Enter your message to encrypt:");
    fflush(stdout);
    read(0,buff,79);
    line = strchr(buff,'\n');
    *line = '\0';
    for(i=0;i<strlen(buff);i++)
       {
         buff[i] = buff[i] ^ key ;
       }
    printf("Your encrypted msg : %s \n",buff);
}


void decrypt()
{
    char key ;
    int i ;
    char *line ;
    char buff[50];
    printf("Enter your key to decrypt:");
    fflush(stdout);
    read(0,&key,2);
    printf("Enter your message to decrypt:");
    fflush(stdout);
    read(0,buff,54);
    line = strchr(buff,'\n');
    *line = '\0';
    for(i=0;i<strlen(buff);i++)
       {
         buff[i] = buff[i] ^ key ;
       }
    printf("Your decrypted msg :");
    printf(buff);
    printf("\n");
   

}



void main()
{  int option;
   printf("***************** Welcome to Xor Tool *********************************\n \n");
   printf("[1] Encrypt\n");
   printf("[2] Decrypt\n");
   printf("[3] Exit \n");
   printf("\n");
   printf("***********************************************************************\n \n");
 
  while(1)
 {
   printf("Enter your option: ");
   scanf("%d",&option);
   switch(option)
    {
        case 1:
            encrypt();
            break;
        case 2 :
            decrypt();
            break ;
        case 3 :
            printf("good bye ...\n");
            exit(0);
    }
  }
}

