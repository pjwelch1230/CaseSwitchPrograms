/* Patrick Welch CSCE 311 Project 4
 *
 * This program primarily uses mmap to switch cases of letters in a file
 * Special thanks to youtuber/coder Jacob Sorber, his video "How to Map Files into
 * Memory in C (mmap, memory mapped file io)" was especially helpful and inspired the
 * design of this program
*/

#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: ./P1.out <filepath>\n");
    exit(-1);
  }
    
  char* path = argv[1];
  
  // Opens file with Read/Write permissions
  int fd = open(path, O_RDWR, S_IRUSR | S_IWUSR);
  printf("fd = %d\n", fd);
  
  printf("Checking if file exists...\n");
  if (fd == -1) {
    printf("Unable to open file... exiting now\n");
    exit(-1);
  }

  // Get file size, fsize, using stat
  struct stat st;
  if (fstat(fd, &st) == -1) {
    printf("Unable to retrieve file size... exiting now...\n");
    exit(-1);
  }
  size_t fsize = st.st_size;
  printf("File size: %ld\n", fsize);
  
  // Mmaps file to char*
  char *p = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    printf("Mapping failed... exiting now\n");
    exit(-1);
  }
  
  printf("Testing map from file:\n%s\n", p);
  
  // Switches cases
  for (int i = 0; i < fsize; i++) {
    if(isupper(p[i])) {
        p[i] = tolower(p[i]);
      }  else {
          p[i] = toupper(p[i]);
      }
  }
  printf("Testing case switch:\n%s\n", p);
  
  munmap(p, fsize);
  close(fd);
}
