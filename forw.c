/* Patrick Welch CSCE 311 Project 4
 *
 * This program uses fopen / fread / fwrite to switch cases of letters in a file
 * Special thanks to M. Kesson of fundza.com, their code on storing file contents to 
 * an allocated buffer was exceptionally helpful
 * 
 * Link to mentioned inspiration: http://www.fundza.com/c4serious/fileIO_reading_all/index.html
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

// Main Method
int main(int argc, char *argv[]) {
  // Check arguments
  if (argc != 2) {
    perror("USAGE: ./orw.out <file path>\n");
    exit(-1);
  }
  
  // Desired file path
  char *fp = argv[1];
  
  // File pointer
  FILE* fptr;
  FILE* fptw;
  
  // Opens file for reading and writing
  fptr = fopen(fp, "r");
  if (fptr == NULL) {
    printf("Couldn't open file for reading\n");
    exit(-1);
  }
  
  // Initializes buffer and reader
  char *buffer;
  ssize_t totalR;
  
  // Gets number of bytes
  fseek(fptr, 0L, SEEK_END);
  totalR = ftell(fptr);
  
  // Resets pointer to beginning of file
  fseek(fptr, 0L, SEEK_SET);
  
  buffer = (char *)calloc(totalR, sizeof(char));
  if (buffer == NULL) {
    printf("Error allocating memory for buffer\n");
    exit(-1);
  }
  // Does all the fun stuff
  printf("Beginning read from file...\n");  
  
  // Reads file into buffer
  fread(buffer, sizeof(char), totalR, fptr);
  fclose(fptr);
  printf("Testing data transfer to buffer:\n%s\n", buffer);
  
  // Switches cases of letters
  for (int i = 0; i < totalR; i++) {
    if(isupper(buffer[i])) {
        buffer[i] = tolower(buffer[i]);
      }  else {
          buffer[i] = toupper(buffer[i]);
      }
  }
  
  printf("Testing case switch:\n%s\n", buffer);
  
  // Opens file with writing permissions
  fptw = fopen(fp, "w");
  if (fptr == NULL) {
    printf("Couldn't open file for reading\n");
    exit(-1);
  }
  
  // Writes buffer to file
  fwrite(buffer, sizeof(char), totalR, fptw);
  
  // Free memory allocated for buffer
  free(buffer);
  
  fclose(fptw);
  return 0;
}
