#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <argp.h>

#include "neander.h"

static char doc[] = "migueldalberto/neander - a simulator for NEANDER hypotetical computer";
static char args_doc[] = "INPUT_MEMORY";

static struct argp_option options[] = {
  { "silent", 's', 0, 0, "Don't print memory to stdout", 0 },
  { "debug", 'd', 0, 0, "Wait to run each instruction", 0 },
  { "output", 'o', "FILE", 0, "Output memory (as bytes) to file", 0 },
  { 0 }
};

#define N_OF_ARGS 1

struct arguments {
  char* args[N_OF_ARGS];
  bool silent;
  bool debug;
  char* outputFile;
};

static error_t parse_opt (int key, char* arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
  case 's':
    arguments->silent = true;
    break;
  case 'd':
    arguments->debug = true;
    break;
  case 'o':
    arguments->outputFile = arg;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= N_OF_ARGS)
      argp_usage(state);

    arguments->args[state->arg_num] = arg;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < N_OF_ARGS)
      argp_usage(state);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main (int argc, char** argv) {
  struct arguments arguments;

  arguments.silent = false;
  arguments.debug = false;
  arguments.outputFile = "";

  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  
  Neander n = {0};

  if (loadMemory(&n, arguments.args[0])) {
    fprintf(stderr, "failed to read file '%s'\n", arguments.args[0]);
  }

  if (arguments.debug) {
    do {
      printNeanderState(n);
    
      char c;
      while ((c=getchar()) != '\n') { }
    
      neanderStepIn(&n);
    } while (!n.halted);
  } else {
    neanderRun(&n);
  }

  if (arguments.outputFile[0] != '\0') {
    if (dumpMemory(n, arguments.outputFile)) {
      fprintf(stderr, "failed to dump memory to file '%s'\n", argv[2]);
    }
  }

  if (!arguments.silent)
    printMemory(n);

  return 0;
}
