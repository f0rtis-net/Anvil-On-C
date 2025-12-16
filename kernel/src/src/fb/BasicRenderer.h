#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "../kernel.h"

struct Point
{
    unsigned int x;
    unsigned int y;
};

typedef enum {
    WHITE = 0xffffffff,
    SILVER = 0xffc0c0c0,
    GRAY = 0xff808080,
    BGRAY = 0xffC0C0C0,
    DGRAY = 0xff404040,
    BLACK = 0xff000000,
    PINK = 0xffFF1493,
    GREEN = 0xff008000,
    RED = 0xff800000,
    PURPLE = 0xff800080,
    ORANGE = 0xffFF4500,
    CYAN = 0xff008080,
    YELLOW = 0xffFFD700,
    BROWN = 0xffA52A2A,
    BLUE = 0xff000080,
    DBLUE = 0xff000030,
    BRED = 0xffFF0000,
    BBLUE = 0xff0000FF,
    BGREEN = 0xff00FF00,
    TBLACK = 0x00000000
}Color_e;

struct PSF1_HEADER
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
};

struct PSF1_FONT
{
    struct PSF1_HEADER *psf1_header;
    void *glyph_buffer;
};

struct Framebuffer
{
    void *base_address;
    size_t buffer_size;
    unsigned int width;
    unsigned int height;
    unsigned int pixels_per_scan_line;
};

typedef struct
{
    struct Point cursor_position;
    struct Framebuffer *framebuffer;
    struct PSF1_FONT *psf1_font;

    unsigned int color;
    bool overwrite;
} BasicRenderer;

void init_renderer(BasicRenderer *basicrenderer, struct Framebuffer *framebuffer, struct PSF1_FONT *psf1_font);

void print(BasicRenderer *basicrenderer, const char* str);
void put_char(BasicRenderer *basicrenderer, char chr, unsigned int xOff, unsigned int yOff);
void clear(BasicRenderer *basicrenderer, uint32_t color, bool resetCursor);

