#ifndef STRINGS_H
#define STRINGS_H

#include <stdint.h>
#include <stddef.h>

void *memset(void *s, int c, size_t n);

void itoa(char *buf, int base, int d);

void *memcpy(void *dest, const void *src, size_t n);

void *memmove(void *dest, const void *src, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);


#endif //STRINGS_H
