
#include <stdio.h>
#include <signal.h>

#define READ 0
#define WRITE 1

int main(){
        FILE *fp;
        char buf[BUFSIZ];

        fp = popen("ls","r");
        while(fgets(buf, BUFSIZ, fp) != NULL)
        fputs(buf, stdout);
}

FILE *popen(const char *command, const char *mode){

        int pfp[2],pid;//the pipe and the process 
        FILE *fdopen(), *fp; //fopen makes a fd a stream
        int parent_end, child_end;//of pipe     
        if(*mode == 'r'){
                parent_end = READ;
                child_end = WRITE;
        }else if(*mode == 'w'){
                parent_end = WRITE;
                child_end = READ;

        }else return NULL;

        if(pipe(pfp) == -1)//get a pipe 
                return NULL;
        if((pid = fork()) == -1){
                close(pfp[0]);
                close(pfp[1]);
                return NULL;
        }
        //parent code here 
        //need to close one end and fdopen other end 
        if(pid > 0) {
                if(close (pfp[child_end]) == -1)
                        return NULL;
                return fdopen(pfp[parent_end],mode);//same mode 

        }
        //child code here 
        // need to redirect stdin or stdout then exec the cmd 
        if(close(pfp[parent_end]) == -1)
                exit(1);
        if(dup2(pfp[child_end],child_end) == -1)
                exit(1);
        if(close(pfp[child_end]) == -1)
                exit(1);
        execl("/bin/sh","sh","-c",command, NULL);
                exit(1);
}
                                                                                                                                                                                                 55,1          All
