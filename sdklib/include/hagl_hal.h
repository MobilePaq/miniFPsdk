#ifndef HAGL_HAL_H
#define HAGL_HAL_H

#include <stdint.h>
#include "hagl/color.h"

void hagl_hal_put_pixel(void *surface, int16_t x, int16_t y, hagl_color_t color);

#define HAGL_HAS_HAL_BACKEND
#define HAGL_COLOR_TYPE 16

#endif /* HAGL_HAL_H */
