#ifndef TTY_H
#define TTY_H

#include "../fb/BasicRenderer.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

void init_tty(struct Framebuffer* framebuffer, struct PSF1_FONT* psf1_font);

void kprintf(const char *fmt, ...);

#endif //TTY_H
