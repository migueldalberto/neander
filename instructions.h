#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "neander.h"

#define NUMBER_OF_INSTRUCTIONS 11

enum InstructionCode {
  NOP = 0x0,
  STA,
  LDA,
  ADD,
  OR,
  AND,
  NOT,
  JMP = 0x8,
  JN,
  JZ,
  HLT = 0xf
};

typedef struct {
  enum InstructionCode code;
  bool hasOperand;
  void (*operation)(Neander*);
} Instruction;

void noOp (Neander *n);
void storeAc (Neander *n);
void loadAc (Neander *n);
void add (Neander *n);
void or (Neander *n);
void and (Neander *n);
void not (Neander *n);
void jump (Neander *n);
void jumpN (Neander *n);
void jumpZ (Neander *n);
void halt (Neander *n);

#endif
