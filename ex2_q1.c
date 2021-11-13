#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>     // for fork, sleep etc.
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int factors(int num);

int open_file(char *name);

#define MAX_NUM_LEN 10

int main(int argc, char* argv[]) {

    char c[MAX_NUM_LEN];
    int num = 1;
    int count = 0;

    while (num > 0) {
        scanf("%s", c);
        count++;

        if (sscanf(c, "%d", &num)) {
            if (fork() == 0) {
                //export to func
                close(1);
                char filename[64];
                sprintf(filename, "%d.tx", num);
                open_file(filename);
                int response = factors(num);
                printf("%d", response);
                exit(response);
            }
        }
    }

    // wait and get primary func
    int primary = 0;
    int status;
    for (int i = 0; i < count; i++) {
        //wait and return status
        wait(&status);
        primary += WEXITSTATUS(status);
    }

    //print_end_msg func
    printf("There were %d prime numbers\n", primary);
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