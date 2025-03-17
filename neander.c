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

void dumpMemory (Neander *n) {
  for (int i = 0; i < MEM_LENGTH; ++i) {
    printf("%x %x\n", i, n->mem[i]);
  }
}
