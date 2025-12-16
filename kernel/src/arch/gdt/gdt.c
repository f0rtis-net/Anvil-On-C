#include "gdt.h"
#include "../../src/tty/tty.h"

#include <stdint.h>

gdt_pointer_t gdtr;
struct {
    gdt_entry_t gdt_entries[5];
    tss_entry_t tss_entry;
} __attribute__((packed)) gdt;
tss_t tss = {0};

#define KERNEL_STACK_SIZE 4096 * 8
char kernel_stack[KERNEL_STACK_SIZE];

extern void _load_gdt(gdt_pointer_t *descriptor);
extern void _reload_segments(uint64_t cs, uint64_t ds);

void gdt_init() {
    gdt.gdt_entries[0] = (gdt_entry_t)GDT_ENTRY(0, 0, 0, 0); // Null Segment
    gdt.gdt_entries[1] =
        (gdt_entry_t)GDT_ENTRY(0, 0xFFFFF, 0x9A,
                               0xA); // 64-bit kernel code segment
    gdt.gdt_entries[2] =
        (gdt_entry_t)GDT_ENTRY(0, 0xFFFFF, 0x92,
                               0xC); // 64-bit kernel data segment
    gdt.gdt_entries[3] =
        (gdt_entry_t)GDT_ENTRY(0, 0xFFFFF, 0xFA,
                               0xA); // 64-bit user code segment
    gdt.gdt_entries[4] =
        (gdt_entry_t)GDT_ENTRY(0, 0xFFFFF, 0xF2,
                               0xC); // 64-bit user data segment

    gdtr.size    = (uint16_t)(sizeof(gdt) - 1);
    gdtr.pointer = (gdt_entry_t *)&gdt;

    tss.rsp0 = (uint64_t)(kernel_stack + KERNEL_STACK_SIZE);

    gdt.tss_entry.limit_low   = sizeof(tss_t);
    gdt.tss_entry.base_low    = (uint16_t)((uint64_t)&tss & 0xffff);
    gdt.tss_entry.base_middle = (uint8_t)(((uint64_t)&tss >> 16) & 0xff);
    gdt.tss_entry.access      = 0x89;
    gdt.tss_entry.limit_high_and_flags = 0;
    gdt.tss_entry.base_high   = (uint8_t)(((uint64_t)&tss >> 24) & 0xff);
    gdt.tss_entry.base_higher = (uint32_t)((uint64_t)&tss >> 32);
    gdt.tss_entry.zero        = 0;

    kprintf("GDTR:\n");
    kprintf("\tsize: %d\n", gdtr.size);
    kprintf("\tpointer: 0x%x\n", gdtr.pointer);

    kprintf("Loading GDTR 0x%x\n", (uint64_t *)&gdtr);
    _load_gdt(&gdtr);

    _reload_segments(GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
}

void set_tss_kernel_stack() {

}