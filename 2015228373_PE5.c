#include <stdio.h>
#include <signal.h>

//#include"iostream"
int main()
{
        //printf("hello");
        //return 0;

        void f(int );//declare the handler
        int i;

        signal(SIGINT, f);//install the handler

        for(  i = 0; i<4; i++)//do something else
        {

//              void f(int);
//              signal(SIGINT,f);
                printf("hello\n");
                sleep(1);

                }




}
void f(int signum)
{

char c;
printf("INterrupt (YES or NO) ?\n");
scanf("%s",&c);

if(c == 'y' || c == 'Y')

exit(0);
 }

~                                                                                                                                                                                                                
~                                                                                                                                                                                                                
~
