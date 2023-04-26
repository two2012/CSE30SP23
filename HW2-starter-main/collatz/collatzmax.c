#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* USAGE_ERROR = "Usage %s n\n";
const char* OUT_OF_BOUNDS_ERRORS = "argument %lld must be > 1 and less than or equal to 4,294,967,295\n";
const char* MAX_STOP_TIME = "Maximum stopping time is %d for n = %lld\n";

unsigned int
compute(unsigned long long num){
    if (num == 1){
        return 0;
    }
    else if (num % 2 == 0){
        return 1 + compute(num/2);
    }
    else{
        return 1 + compute(3*num + 1);
    }
}

int
main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, USAGE_ERROR, argv[0]);
        return EXIT_FAILURE;
    }
    unsigned long long x = strtoull(argv[1], NULL, 10);
    if (x <= 1 || x > 4294967295ull){
        fprintf(stderr, OUT_OF_BOUNDS_ERRORS, x);
        return EXIT_FAILURE;
    }

    int max_stopping_time = 0;
    unsigned long long max_stopping_time_n = 0;
    for (unsigned long long i = 2; i < x; i++) {
        int stopping_time = compute(i);
        if (stopping_time > max_stopping_time) {
            max_stopping_time = stopping_time;
            max_stopping_time_n = i;
        }
    }
    printf(MAX_STOP_TIME, max_stopping_time, max_stopping_time_n);
    return EXIT_SUCCESS;
}
