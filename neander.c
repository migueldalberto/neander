#include <stdio.h>

#include "neander.h"
#include "instructions.h"

Instruction decode(uint8_t);

Instruction instructionSet[NUMBER_OF_INSTRUCTIONS] = {
  { .code = NOP, .hasOperand = false, .operation = noOp },
  { .code = STA, .hasOperand = true, .operation = storeAc },
  { .code = LDA, .hasOperand = true, .operation = loadAc },
  { .code = ADD, .hasOperand = true, .operation = add },
  { .code = OR, .hasOperand = true, .operation = or },
  { .code = AND, .hasOperand = true, .operation = and },
  { .code = NOT, .hasOperand = false, .operation = not },
  { .code = JMP, .hasOperand = true, .operation = jump },
  { .code = JN, .hasOperand = true, .operation = jumpN },
  { .code = JZ, .hasOperand = true, .operation = jumpZ },
  { .code = HLT, .hasOperand = false, .operation = halt }
};

void startNeander (Neander *n) {
  n->halted = false;
  while (!n->halted) {
    // search instruction
    n->ri = n->mem[n->pc] >> 4;
    n->pc++;

    // decode instruction
    Instruction inst = decode(n->ri);

    if (inst.hasOperand){
      n->rem = n->mem[n->pc];
      n->pc++;
    }

    // execute
    inst.operation(n);
  }
}

Instruction decode(uint8_t inst) {
  for (int i = 0; i < NUMBER_OF_INSTRUCTIONS; ++i) {
    if (instructionSet[i].code == inst)
      return instructionSet[i];
  }

  return instructionSet[0];
}

int loadMemory (Neander *n, const char* filename) {
  FILE* f = fopen(filename, "r");

  if (f == NULL || n == NULL)
    return 1;

  uint8_t buf[0x204] = {0};

  int bytesRead = fread(buf, sizeof(uint8_t), 0x204, f);
  fclose(f);

  if (bytesRead != 0x204) {
    return 1;
  }

  for (int i = 4; i < 0x204; i +=2) {
    n->mem[(i - 4) / 2] = buf[i];
  }

  return 0;
}

int dumpMemory (Neander *n, const char* filename) {
  FILE* f = fopen(filename, "w");

  if (f == NULL || n == NULL) {
    return 1;
  }

  uint8_t buf[0x204] = {0};
  buf[0] = 0x03;
  buf[1] = 0x4e;
  buf[2] = 0x44;
  buf[3] = 0x52;

  for (int i = 4; i < 0x204; i += 2) {
    buf[i] = n->mem[(i - 4) / 2];
  }
    
  fwrite(buf, sizeof(uint8_t), 0x204, f);
  fclose(f);

  return 0;
}
