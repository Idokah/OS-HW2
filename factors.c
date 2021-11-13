#include <stdio.h>
#include <stdlib.h>
int get_factors(int num);

int main(int argc, char* argv[]){
    int num = 0;
    sscanf(argv[1],"%d", &num);
    return (get_factors(num));
}

int get_factors(int num) {
    int primary = 1;
    for (int i = 1 ; i <= num; i++) {
        if (num%i == 0) {
            printf("%d ", i);
            if (i!=1 && i!=num)
                primary = 0;
        }
    }
    return primary;
}