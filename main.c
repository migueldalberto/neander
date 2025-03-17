#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "neander.h"

int main (int argc, char** argv) {
  Neander n = {0};

  n.mem[0x01] = 0xf0;

  if (argc > 1) {
    if (loadMemory(&n, argv[1])) {
      fprintf(stderr, "failed to read file '%s'\n", argv[1]);
    } 
  }
 
  startNeander(&n);

  if (dumpMemory(&n, "out.mem")) {
    fprintf(stderr, "failed to dump memory to file '%s'\n", "b.mem");
  }

  return 0;
}
