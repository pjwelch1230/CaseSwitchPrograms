/* Patrick Welch CSCE 311 Project 4
 * This program uses Open / Read / Write to switch cases of letters in a file
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#define BUF_SIZE 4096

// Main Method
int main(int argc, char *argv[]) {
  // Check arguments
  if (argc != 2) {
    perror("USAGE: ./orw.out <file path>");
    exit(-1);
  }
  // Desired file path
  char *fp = argv[1];
  
  // Opens file for reading
  int fdr = open(fp, O_RDONLY | O_EXCL);
  printf("fdr = %d\n", fdr);
  if (fdr == -1) {
    printf("Error %d\n", errno);
    perror("Program");
    exit(-1);
  }
  
  // Opens file for writing
  int fdw = open(fp, O_WRONLY | O_EXCL);
  printf("fdw = %d\n", fdw);
  if (fdr == -1) {
    printf("Error %d\n", errno);
    perror("Program");
    exit(-1);
  }
  
  // Initializes buffer and reader
  char buffer[BUF_SIZE];
  ssize_t reader;
  
  // Does all the fun stuff
  printf("Beginning read from file...\n");  
  
  while(1) {
    // Gets number of bytes read
    reader = read(fdr, buffer, sizeof(buffer));
    printf("\nreading...\n");
    
    // If there is less bytes left in file than size of buffer do this
    if (reader < sizeof(buffer)) {
      buffer[reader] = '\0';
      for (int i = 0; i < reader; i++) {
        if(isupper(buffer[i])) {
          buffer[i] = tolower(buffer[i]);
        }  else {
            buffer[i] = toupper(buffer[i]);
        }
      }
      printf("%s\n", buffer);
      write(fdw, buffer, reader);
      break;
      } 
      
      // ELSE STATEMENT------------------------------
      
      for (int i = 0; i < sizeof(buffer); i++) {
        if(isupper(buffer[i])) {
          buffer[i] = tolower(buffer[i]);
        }  else {
            buffer[i] = toupper(buffer[i]);
        }
      }
      printf("Buffer: %s\n", buffer);
      write(fdw, buffer, sizeof(buffer));
  }
  
  close(fdr);
  close(fdw);
}
