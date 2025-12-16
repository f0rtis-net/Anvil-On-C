#include "tty.h"
#include "../../utils/strings/strings.h"

static BasicRenderer r;

void init_tty(struct Framebuffer* framebuffer, struct PSF1_FONT* psf1_font) {
    init_renderer(&r, framebuffer, psf1_font);

    clear(&r, BLACK, true); 
}

void console_putchar(char c) {
    char memes[] = {c};
    print(&r, memes);
}

void print_padded(const char *str, int pad0, int pad) {
    // Calculate length
    int len = 0;
    const char *p = str;
    while (*p++) len++;
    
    // Add padding
    while (len++ < pad) {
        console_putchar(pad0 ? '0' : ' ');
    }
    
    // Print string
    p = str;
    while (*p) {
        console_putchar(*p++);
    }
}

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    char buf[32];
    
    while (*fmt) {
        if (*fmt != '%') {
            console_putchar(*fmt++);
            continue;
        }
        
        fmt++; // Skip '%'
        
        // Handle padding (optional)
        int pad0 = 0;
        int pad = 0;
        
        if (*fmt == '0') {
            pad0 = 1;
            fmt++;
        }
        
        if (*fmt >= '0' && *fmt <= '9') {
            pad = *fmt - '0';
            fmt++;
        }
        
        switch (*fmt) {
            case 'd': {
                int value = va_arg(args, int);
                itoa(buf, 'd', value);
                print_padded(buf, pad0, pad);
                break;
            }
            case 'u': {
                unsigned int value = va_arg(args, unsigned int);
                itoa(buf, 'u', (int)value);
                print_padded(buf, pad0, pad);
                break;
            }
            case 'x': {
                unsigned int value = va_arg(args, unsigned int);
                itoa(buf, 'x', (int)value);
                print_padded(buf, pad0, pad);
                break;
            }
            case 's': {
                char *str = va_arg(args, char*);
                if (!str) str = "(null)";
                print_padded(str, pad0, pad);
                break;
            }
            case 'c': {
                char c = (char)va_arg(args, int);
                console_putchar(c);
                break;
            }
            case '%': {
                console_putchar('%');
                break;
            }
            default:
                // Unknown specifier
                console_putchar('%');
                console_putchar(*fmt);
                break;
        }
        fmt++;
    }
    
    va_end(args);
}