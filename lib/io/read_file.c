#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/**
 * Returned pointer must be freed once it is not needed.
 */
char *read_file(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  long length = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = malloc(length + 1);

  fread(buffer, 1, length, fp);
  buffer[length] = 0,

  fclose(fp);
  return buffer;
};