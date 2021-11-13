#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>     // for fork, sleep etc.
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "ex2_q1.h"



int main(int argc, char* argv[]) {
    for (int i = 1 ; i < argc; i++){
        child_exec_factors(argv[i]);
    }
    int primary_count = 0;
    for (int i =0 ; i < argc ; i++) {
        primary_count += wait_and_is_primary();
    }

    print_end_msg(primary_count);
}

void child_exec_factors(char* input) {
    if (fork() == 0) {
        int num = sscanf(input, "%d", &num);
        replace_stdout(num);
        execve(PROG_NAME, create_argv(input), NULL);
    }
}

char** create_argv(char* input) {
    char** my_argv = (char**) malloc(sizeof(char*)*3);
    my_argv[0]=PROG_NAME;
    my_argv[1] = (char*) malloc(strlen(input) + 1);
    my_argv[2] = NULL;
    strcpy(my_argv[1],input);
    return my_argv;
}
int replace_stdout(int num){
    char filename[MAX_FILE_LEN];
    sprintf(filename, "%d.tx", num);
    close(1);
    return open_file(filename);
}

int wait_and_is_primary(){
    int status;
    wait(&status);
    return WEXITSTATUS(status);
}

void print_end_msg(const int num_primes)
{
    printf("There were %d prime numbers\n", num_primes);
}

int open_file(char *name) {
    int fd;
    fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0)  // open failed
    {
        fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", name, fd);
        exit(2);
    }
    return (fd);
}