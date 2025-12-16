bits 64

global _load_gdt
_load_gdt:
    lgdt [rdi]
    push ax
    mov ax, 0x28
    ltr ax
    pop ax
    ret

global _reload_segments
_reload_segments:
    push rdi        ; cs (rdi & 0xFF)

    lea rax, [.reload_cs]
    push rax

    retfq
.reload_cs:
    mov ax, si      ; ds
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret