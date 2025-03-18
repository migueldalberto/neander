#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "neander.h"

int main (int argc, char** argv) {
  Neander n = {0};

  if (argc == 1 || argc > 3) {
    fprintf(stderr, "bad arguments\n");
    fprintf(stderr, "usage: %s INPUT OUTPUT\n", argv[0]);
    return 1;
  }

  if (loadMemory(&n, argv[1])) {
    fprintf(stderr, "failed to read file '%s'\n", argv[1]);
  } 
   
  startNeander(&n);

  if (argc == 3) {
    if (dumpMemory(n, argv[2])) {
      fprintf(stderr, "failed to dump memory to file '%s'\n", argv[2]);
    }
  }

  printMemory(n);

  return 0;
}
