#include "cpu/exec.h"
#include "memory/mmu.h"

void raise_intr(uint8_t NO, vaddr_t ret_addr) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
  rtl_push(&cpu.eflags);
  rtl_li(&t0, cpu.cs);
  rtl_push(&t0);
  rtl_push(&cpu.eip);
  GateDesc gatedesc;
  vaddr_t addr = cpu.idtr.base + NO * sizeof(GateDesc);
  Log("cpu.idtr.base=%x NO=%x addr = %x", cpu.idtr.base, NO, addr);
  gatedesc.val = vaddr_read(addr, 4);
  decoding.jmp_eip = ((gatedesc.offset_31_16 << 16) | gatedesc.offset_15_0) + cpu.eip;
  rtl_j(decoding.jmp_eip);
}

void dev_raise_intr() {
}
