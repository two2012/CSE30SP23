#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* USAGE_ERROR = "Usage %s starting_number\n";
const char* OUT_OF_BOUNDS_ERRORS ="argument %lld must be > 0 and less than or equal to 2,147,483,647\n";
const char* STOP_TIME = "n = %lld has a stopping time of %d\n";


unsigned int
compute(unsigned long long num){
  //TODO: Implement the recursive Collatz 
  // checking to see if the number is even or odd
  if (num == 1){
    return 0;
  }
  else if (num % 2 == 0){
    
    return 1 + compute(num/2);
  }
  else{
    return 1+ compute(3*num + 1);
  }

}

int
main(int argc, char **argv){
  //TODO: Implement input processing
  if (argc != 2){
    fprintf(stderr, USAGE_ERROR, argv[0]);
    return EXIT_FAILURE;
  }
  long long x = atoll(argv[1]);
  if (x <= 0 || x > 2147483647ll){
    fprintf(stderr, OUT_OF_BOUNDS_ERRORS, x);
    return EXIT_FAILURE;
  }

  //TODO: Get stopping time
  int stopping_time = compute(x);
  printf(STOP_TIME, x, stopping_time);
  return EXIT_SUCCESS;
}

