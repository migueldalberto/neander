#include <stdio.h>

#include "instructions.h"

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
  n->ac += n->mem[n->rem];
  
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
