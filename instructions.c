#include <stdio.h>

#include "instructions.h"

#define N_OF_BITS 8
#define CALC_COMPLEMENT (x) 0x100 - x

void setRst (Neander *n) {
  if (n->ac == 0)
    n->rst.z = true;
  else
    n->rst.z = false;

  if (n->ac > 127)
    n->rst.n = true;
  else
    n->rst.n = false;
}

void loadAc (Neander *n) {
  n->ac = n->mem[n->rem];
  setRst(n);
}

void noOp (Neander *n) { return; }

void storeAc (Neander *n) {
  n->mem[n->rem] = n->ac;
}

void add (Neander *n) {
  int acNumber;
  
  if (n->ac > 256 / 2)
    acNumber = - (256 - n->ac);
  else
    acNumber = n->ac;

  int endNumber;
  
  if (n->mem[n->rem] > 256 / 2)
    endNumber = - (256 - n->mem[n->rem]);
  else
    endNumber = n->mem[n->rem];

  if (acNumber + endNumber > 127)
    acNumber += endNumber - 127;
  else if (acNumber + endNumber < -127)
    acNumber += endNumber + 127;
  else
    acNumber += endNumber;

  if (acNumber < 0)
    n->ac = 256 + acNumber;
  else
    n->ac = acNumber;
  
  setRst(n);
}

void or (Neander *n) {
  n->ac = n->ac | n->mem[n->rem];
}

void and (Neander *n) {
  n->ac = n->ac & n->mem[n->rem];
}

void not (Neander *n) {
  n->ac = ~n->ac;
}

void jump (Neander *n) {
  n->pc = n->rem;
}

void jumpN (Neander *n) {
  if (n->rst.n)
    jump(n);
}

void jumpZ (Neander *n) {
  if (n->rst.z)
    jump(n);
}

void halt (Neander *n) {
  n->halted = true;
}
