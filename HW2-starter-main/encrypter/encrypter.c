#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256 // maximum length of a single word
extern char rotate(char, int);

int main(int argc, char* argv[]) {

  //char word[MAX_LEN];
  int n = atoi(argv[2]);

  FILE* fin = fopen( /* TODO: Read from input file */argv[1], "r");

  if(fin == NULL) {
    perror("Could not open input file.");
    return EXIT_FAILURE;
  }

  //checking number of arguments
  if (argc != 3){
    fprintf(stderr, "Usage: encrypter number of arguments not match\n");
    return EXIT_FAILURE;
  }
 
  // TODO: Write your code here to implement the encryption.
  int input;

  while ((input = fgetc(fin)) != EOF){
    printf("%c", rotate(input, n));
  }

  // clean up gracefully
  fclose(fin);

  return EXIT_SUCCESS;
}

char rotate(char input, int n) {
  // check if input is a letter
  if (input >= 'a' && input <= 'z') {
    // rotate lowercase letters
    return 'a' + (input - 'a' + n) % 26;
  } else if (input >= 'A' && input <= 'Z') {
    // rotate uppercase letters
    return 'A' + (input - 'A' + n) % 26;
  } else {
    // do not rotate non-letters
    return input;
  }
}
