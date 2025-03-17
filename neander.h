#ifndef NEANDER_H
#define NEANDER_H

#include <stdint.h>
#include <stdbool.h>

#define MEM_LENGTH 256

typedef struct {
  uint8_t ac;
  uint8_t pc;
  struct {
    bool n;
    bool z;
  } rst;
  uint8_t ri;
  uint8_t rem;
  uint8_t mem[MEM_LENGTH];
  bool halted;
} Neander;

void startNeander (Neander*);
int dumpMemory (Neander*, const char*);
int loadMemory (Neander*, const char*);

#endif
