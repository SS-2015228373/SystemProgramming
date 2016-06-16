include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define oops(m,x)  {perror(m); exit(x) ;}
main(int ac, char **av)
{
        int thepipe[2],   //first pipe for the first and second command
            thesecondpipe[2], //second pipe for the second and third commands
            pid; //and the pid
        if( ac != 4){

                fprintf(stderr, "usage: pipe cmd1 cmd2 cmd3 \n");
                exit(1);

                   }
        if(pipe (thepipe ) ==  -1) //get the first pipe
                oops("Cannot get a pipe ",1);
        if( pipe (thesecondpipe) == -1)  //get the secnd pipe
                oops("Cannot get a pipe",1);
        if((pid = fork()) == -1) //get the first child for executing first command 
        oops("Cannot fork",2);
        if(pid == 0) {
                //first child reads from the stdin, executes the first command and writes the output to the first pipe
                close(thesecondpipe[0]); //first child doesn't read or write the second pipe 
                close(thesecondpipe[1]);//first child doesn't read form the first pipe 
                close(thepipe[0]); //first child doesn't read from the first pipe 
                if(dup2(thepipe[1],1) == -1)
                        oops("could not redirect stdout",4);
                close(thepipe[1]);  //stdout is duped, close the first pipe write end 
                execlp( av[1],av[1],NULL);
                oops(av[1],5);


        }
                if( pid >0){
                                        if((pid = fork())==-1) //create the second child to execute the second command 
                                oops("Cannot fork",2);
                        if(pid == 0){

                                //seond child reads from the first pipe, executes the second command and writes the output to the second pipe 
                                 close(thepipe[1]);//second child doesn't write to the first pipe 
                                if( dup2(thepipe[0],0) == -1)
                                        oops("Could not redirect stdin",3);
                                close(thepipe[0]); //stdin is duped, close the first pipe read  end

                                close(thesecondpipe[0]); //second child doesn't read from the second pipe 

                                if(dup2(thesecondpipe[1],1) == -1)
                                        oops("Could not redirect stdout",3);
                                close(thesecondpipe[1]);// stdout is duped, close the second pipe write end
                                execlp( av[2],av[2],NULL);
                                oops(av[2],5);
                        }
                        if(pid > 0){
                                //parent process reads from the second pipe, executes the third command and write the output to the stdout 
                                close(thepipe[0]);
                                //parent doesn't read or write the first pipe 
                                close(thepipe[1]);
                                close(thesecondpipe[1]);
//parent doesn't write to the second pipe 
                                if(dup2(thesecondpipe[0],0) == -1)
                                        oops("Could not redirect stdin",3);
                                close(thesecondpipe[0]); //stdin is duped , close the second pipe read end 
                                execlp( av[3],av[3],NULL);
                                oops(av[2],4);
                                                        }


                }
        }
                                 
                                                
