
#ifndef HW2_EX2_Q1_H
#define HW2_EX2_Q1_H

#define MAX_NUM_LEN 10 //delete
#define MAX_FILE_LEN 15
#define PROG_NAME "factors"

int open_file(char *name);
void child_exec_factors(char* input);
int replace_stdout(int num);
char** create_argv(char* input);
int wait_and_is_primary();
void print_end_msg(const int num_primes);

#endif //HW2_EX2_Q1_H
