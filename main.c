#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/clonefile.h>
#define BUFFER_SIZE 1024
// https://news.ycombinator.com/item?id=29358499
int main() {
  FILE *input;

  // Userspace
  // read the file into program memory and then write it out to another file.
  clock_t start_time = clock();
  input = fopen("input.dat", "rb");

  if (input == NULL) {
    perror("Error opening file");
    return 1;
  }

  FILE *output = fopen("userspaceoutput.dat", "w");

  if (output == NULL) {
   perror("Error opening output file");
   return 1;
  }

  char buffer[BUFFER_SIZE];

  int bytesRead;
  while((bytesRead = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
    fwrite(buffer, 1, bytesRead, output);
  }

  fclose(input);
  fclose(output);
  double elapsed = (double)(clock() - start_time)/CLOCKS_PER_SEC;
  printf("Userspace: Done in %f seconds\n", elapsed);

  //clonefile
  //https://man7.org/linux/man-pages/man2/copyfile_range.2.html
  start_time = clock();
  clonefile("input.dat", "copyfile.dat", CLONE_NOFOLLOW);
  elapsed = (double)(clock() - start_time)/CLOCKS_PER_SEC;
  printf("copyfile: Done in %f seconds\n", elapsed);


  return 0;
}
