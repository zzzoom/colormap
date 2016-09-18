#include <stdint.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "colormap.h"

#define WIDTH 800
#define HEIGHT 50

static void paint_ramp(colormap cm, uint8_t * ramp) {
    for (int i = 0; i < WIDTH; ++i) {
        colormap_rgb(cm, i, 0.0f, WIDTH - 1, &ramp[i * 3], &ramp[i * 3 + 1], &ramp[i * 3 + 2]);
    }
    for (int i = 1; i < HEIGHT; ++i) {
        memcpy(&ramp[i * WIDTH * 3], ramp, WIDTH * 3);
    }
}

int main() {
    uint8_t ramp[WIDTH * HEIGHT * 3];

    paint_ramp(COLORMAP_VIRIDIS, ramp);
    stbi_write_png("viridis.png", WIDTH, HEIGHT, 3, ramp, 3 * WIDTH);

    paint_ramp(COLORMAP_MAGMA, ramp);
    stbi_write_png("magma.png", WIDTH, HEIGHT, 3, ramp, 3 * WIDTH);

    paint_ramp(COLORMAP_PLASMA, ramp);
    stbi_write_png("plasma.png", WIDTH, HEIGHT, 3, ramp, 3 * WIDTH);

    paint_ramp(COLORMAP_INFERNO, ramp);
    stbi_write_png("inferno.png", WIDTH, HEIGHT, 3, ramp, 3 * WIDTH);

    return 0;
}

