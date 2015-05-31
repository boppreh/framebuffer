#include "framebuffer.c"

int main()
{
    struct frame_buffer fb = new_frame_buffer();

    fill_rect(fb, 0, 0, fb.width, fb.height, 0,45,54);

    rect(fb, 200, 200, fb.width-200, fb.height-200, 4, 88,110,117);
    fill_rect(fb, 200, 200, fb.width-200, fb.height-200, 7,54,66);

    destroy_frame_buffer(fb);
    return 0;
}
