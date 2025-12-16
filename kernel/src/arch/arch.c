#include "arch.h"
#include "../src/tty/tty.h"
#include "gdt/gdt.h"

void setup_basic_arch() {
    kprintf("Selected x86_64 arch.\n");

    kprintf("Initialize gdt...\n");
    gdt_init();
    kprintf("Gdt initialized.\n");
}