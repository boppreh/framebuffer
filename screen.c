#include "framebuffer.c"
#include <time.h>
#include <stdlib.h>

static struct frame_buffer fb;

float max(float a, float b) {
    return a > b ? a : b;
}

void draw_dir(char *path, int start_x, int start_y, float scale) {
    if (scale < 1.0/100) {
        return;
    }

    int end_x = start_x + 500 * scale;
    int end_y = start_y + 300 * scale;
    fill_rect(fb, start_x, start_y, end_x, end_y, 7,54,66);

    int end_sub_x = end_x - 10 * scale;
    int end_sub_y = end_y - 10 * scale;
    int start_sub_x = end_sub_x - scale * 400;
    int start_sub_y = end_sub_y - scale * 250;
    fill_rect(fb, start_sub_x, start_sub_y, end_sub_x, end_sub_y, 0,45,54);

    float sub_scale = scale / 6;
    int n_children = rand() % 15;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            draw_dir("/",
                     start_sub_x + max(1, 5 * scale) + (col * (sub_scale * 500 + 5 * scale)),
                     start_sub_y + max(1, 5 * scale) + (row * (sub_scale * 300 + 5 * scale)),
                     sub_scale);
        }
    }

    rect(fb, start_sub_x, start_sub_y, end_sub_x, end_sub_y, max(1, 4*scale), 88,110,117);
    rect(fb, start_x, start_y, end_x, end_y, max(1, 4*scale), 181,137,0);
}

int main()
{
    fb = new_frame_buffer();
    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        fill_rect(fb, 0, 0, fb.width, fb.height, 0,45,54);
        int screen_x = -100 - i * 10;
        int screen_y = -100 - i * 10;
        float scale = 1;
        draw_dir("/", -screen_x, -screen_y, scale);
    }

    destroy_frame_buffer(fb);
    return 0;
}
