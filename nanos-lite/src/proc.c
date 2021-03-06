#include "proc.h"

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used));
static PCB pcb_boot;
PCB *current, *fg_pcb;
PCB* pcbs[MAX_NR_PROC];
static int count = 0;

void naive_uload(PCB* pcb, const char* filename);
void context_kload(PCB *pcb, void *entry);
void context_uload(PCB *pcb, const char *filename);

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite for the %dth time!", j);
    j ++;
    _yield();
  }
}

void init_proc() {
  // context_kload(&pcb[0], (void*)hello_fun);
  // context_uload(&pcb[1], "/bin/dummy");
  // context_uload(&pcb[2], "/bin/bmp");
  context_uload(&pcb[0], "/bin/hello");
  context_uload(&pcb[1], "/bin/pal");
  context_uload(&pcb[2], "/bin/litenes");
  pcbs[0] = &pcb[0];
  pcbs[1] = &pcb[1];
  pcbs[2] = &pcb[2];
  fg_pcb = &pcb[1];
  switch_boot_pcb();
}

_Context* schedule(_Context *prev) {
  current->tf = prev;
  current = fg_pcb;
  // current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  if (current == fg_pcb) {
    count++;
  }
  if (count == 100) {
    count = 0;
    current->tf = prev;
    current = &pcb[0];
  }
  return current->tf;
}
