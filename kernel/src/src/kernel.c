#include "kernel.h"
#include "../arch/arch.h"
#include "tty/tty.h"

void kernel()
{
    kprintf("Arch startup init...\n");
    setup_basic_arch();

    return;
}
