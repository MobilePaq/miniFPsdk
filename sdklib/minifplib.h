#ifndef MINIFPLIB_H
#define MINIFPLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "syscode.h"
#include "hagl.h"
#include "hagl_hal.h"

#define RGB(r,g,b) (uint16_t)((((r)>>3)<<11) | (((g)>>2)<<5) | ((b)>>3))

__attribute__((weak)) uint16_t *fb = NULL;
__attribute__((weak)) void *fb_mem = NULL;

void lcd_appinit(void) {
    sys_data.display.w2 = sys_data.display.w1;
    sys_data.display.h2 = sys_data.display.h1;
}
void draw_textf(hagl_backend_t *surface, int x, int y, uint32_t color, const unsigned char *font, const char *fmt, ...) {
    char buf[64];
    wchar_t wbuf[64];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    for (int i = 0; i < 64; i++) {
        wbuf[i] = (wchar_t)buf[i];
        if (buf[i] == '\0') break;
    }

    hagl_put_text(surface, wbuf, x, y, color, font);
}
int get_pressed_key(void) {
    int type, key;
    type = sys_event(&key);
    if (type == EVENT_KEYDOWN) {
        key &= 0x7fff;
        //printf("KEY: 0x%02x\n", key);
        return key;
    }
    return 0; 
}

void keytrn_init(void) {
    uint8_t keymap[64];
    sys_getkeymap(keymap);
    for (int i = 0; i < 64; i++) {
        sys_data.keytrn[0][i] = keymap[i];
        sys_data.keytrn[1][i] = keymap[i] | (1 << 15);
    }
}

void hagl_hal_put_pixel(void *surface, int16_t x, int16_t y, hagl_color_t color) {
    (void)surface; 
    if (!fb) return;
    if (x < 0 || x >= sys_data.display.w2 || y < 0 || y >= sys_data.display.h2) return;
    fb[y * sys_data.display.w2 + x] = (uint16_t)color;
}

void hagl_hal_init(hagl_backend_t *backend) {
    backend->width = sys_data.display.w2;
    backend->height = sys_data.display.h2;
    backend->put_pixel = hagl_hal_put_pixel;
}
static inline void fp_clear_fast(void) {
    if (fb) {
        memset(fb, 0, sys_data.display.w2 * sys_data.display.h2 * 2);
    }
}
static inline hagl_backend_t* fp_init_all(void) {
	//printf("HELLO! miniFPsdk based on fpdoom, by MobilePaq. Enjoy your homebrew!\n");
    struct sys_display *disp = &sys_data.display;
    disp->w2 = disp->w1; 
    disp->h2 = disp->h1;
    if (!fb_mem) {
        size_t size = disp->w2 * disp->h2;
        fb_mem = malloc(size * 2 + 31);
        uint8_t *p = (uint8_t*)fb_mem;
        p += -(intptr_t)p & 31;
        fb = (uint16_t*)p;
    }
    //printf("Initialized screen!\n");
    sys_framebuffer(fb);
    sys_start();
    //printf("FB init!\n");
    return hagl_init();
}

static inline void fp_update(void) {
    sys_start_refresh();
    sys_wait_refresh();
}

#endif // MINIFPLIB_H
