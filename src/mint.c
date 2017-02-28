#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void func()
{
  char text[50];
  char tmp[20];
  int choice=0 , opt=0 ;
  char *p,*ptr;

  printf("[1] Add text\n");
  printf("[2] Edit text\n");
  printf("[3] Display text\n");
  printf("[4] Exit\n");
 while(1)
  { 
    printf("Enter ur option :");
    scanf("%d",&choice);
    switch(choice)
     {
        case 1:
                 fflush(stdout);
                 read(0,text,50);
                 p = strchr(text,'\n');
                 *p = '\0';
        continue;
        
        case 2:
                 printf("[1] Append text\n");
                 printf("[2] Overwrite\n");  
                 scanf("%d",&opt);
                 if(opt == 1)
                     {
                         fflush(stdout);
                         read(0,tmp,20);
                         ptr= strchr(tmp,'\n');
                         *ptr = '\0';
                        strcat(text,tmp);      
                     }
                 else
                     {
                        fflush(stdout);
                        read(0,tmp,20);
                     }
         continue;

         case 3 :
                    printf("%s\n",text);
          continue;
         
         case 4 :
               
         break;
      } 
         break;
   }

}

void main()
{
    printf("^^^^^^^^^^^^^^ Welcome to My Mini Text editor (Mint)  ^^^^^^^^^^^^^^^^^^^^^^^^\n");
    func();
}
