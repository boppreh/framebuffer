#include "framebuffer.c"

int main()
{
    struct frame_buffer fb = new_frame_buffer();

    int x, y;
    for (y = 0; y < fb.height; y++) {
        for (x = 0; x < fb.width; x++) {
            unsigned char r = 0xFF * x / fb.width;
            unsigned char g = 0xFF * x / fb.width;
            unsigned char b = 0xFF * x / fb.width;
            set_pixel(fb, x, y, r, g, b);
        }
    }

    destroy_frame_buffer(fb);
    return 0;
}
