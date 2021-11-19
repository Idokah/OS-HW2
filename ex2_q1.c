#include "ex2_q1.h"

int main(int argc, char* argv[]) {
    for (int i = 1 ; i < argc; i++){
        child_exec_factors(argv[i]);
    }

    int primary_count = 0;
    for (int i =0 ; i < argc-1 ; i++) {
        primary_count += wait_and_is_primary();
    }

    print_end_msg(primary_count);
}

void child_exec_factors(char* input) {
    if (do_fork() == 0) {
        char* my_argv[3];
        char program_input[MAX_NUM_LEN];
        char fileName[MAX_FILE_LEN];

        sprintf(fileName, "%s.tx", input);

        sprintf(program_input,"%s", input);

        my_argv[0] = PROG_NAME;
        my_argv[1] = program_input;
        my_argv[2] = NULL;

        int num = 0;
        sscanf(input, "%d", &num);
        replace_stdout(num);
        execve(PROG_NAME, my_argv, NULL);
    }
}


int replace_stdout(int num){
    printf("%d",num);
    char filename[MAX_FILE_LEN];
    sprintf(filename, "%d.txt", num);
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
    printf("%s",name);
    fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0)  // open failed
    {
        fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", name, fd);
        exit(2);
    }
    return (fd);
}

int do_fork() {
    int pid = fork();
    if (pid < 0) {
        perror("Cannot fork()");
        exit(EXIT_FAILURE);
    }
    return pid;
}