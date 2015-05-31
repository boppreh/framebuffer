#include "framebuffer.c"

int main()
{
    struct frame_buffer fb = new_frame_buffer();

    fill_rect(fb, 0, 0, fb.width, fb.height, 0,45,54);
    line_x(fb, 0, 500, fb.width, 10, 255,0,0);

    destroy_frame_buffer(fb);
    return 0;
}
