

#include <stdio.h>
#include <signal.h>

#define MAXARGS 20
#define ARGLEN 100

main()
{
        char *arglist[MAXARGS + 1];
        int numargs;
        char argbuf[ARGLEN];
        char *makestring();
        int i;
        numargs = 0;
        void f(int);


        while(numargs < MAXARGS)
        {
                printf("Arg[%d]?", numargs);
                if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n')
                        arglist[numargs++] = makestring(argbuf);
                else
                {
                        if(numargs > 0){                //any args
                                arglist[numargs] = NULL;//close list 
                                execute(arglist);
                                numargs = 0;

                                printf("hello\n");
                                printf("HELLO\n");
                                        }

                }

        }
//      signal(SIGINT,f);
//      if(*argbuf == '\n' )
//{     printf("hello\n ");

//              printf("HELLO\n");

//                           }  




        return 0;

}

void f(int signum)
{
        exit(0);
}

execute(char *arglist[])
//use fork and execvp and wait to do it 
{

        int pid,exitstatus;
        pid = fork();
        switch(pid){
                case -1:
                        perror("fork failed");
                        exit(1);
                case 0:
                        execvp(arglist[0],arglist);
                        perror("execvp failed");
                        exit(1);
                default:
                        while(wait(&exitstatus) != pid )
                                ;
                        printf("child exited with status %d,%d\n",exitstatus>>8,exitstatus&0377);

                }
}

char *makestring (char *buf)
//trim off newline and create storage for the string 
{

        char *cp , *malloc();
        buf[strlen(buf)-1] = '\0';
        cp = malloc(strlen(buf) + 1); //get memory 
        if(cp == NULL){

                fprintf(stderr, "no memory \n");
                exit(1);
        }
        strcpy(cp,buf);
        return cp;
}


~                                                                               
~                                                                               
~                                                                               
-- INSERT --                          
