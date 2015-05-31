#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

struct frame_buffer {
    int file_descriptor;

    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;

    int width;
    int height;

    long int buffer_size;
    char *buffer;
};

struct frame_buffer new_frame_buffer() {
    struct frame_buffer fb;

    fb.file_descriptor = open("/dev/fb0", O_RDWR);
    if (fb.file_descriptor == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    if (ioctl(fb.file_descriptor, FBIOGET_FSCREENINFO, &fb.fixed_info) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    if (ioctl(fb.file_descriptor, FBIOGET_VSCREENINFO, &fb.var_info) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    if (fb.var_info.bits_per_pixel != 32) {
        fb.var_info.bits_per_pixel = 32;
        if (ioctl(fb.file_descriptor, FBIOPUT_VSCREENINFO, &fb.var_info) == -1) {
            perror("Error setting screen color depth.");
            exit(4);
        }
    }

    fb.width = fb.var_info.xres;
    fb.height = fb.var_info.yres;

    fb.buffer_size = fb.width * fb.height * fb.var_info.bits_per_pixel / 8;
    fb.buffer = (char*) mmap(0,
                             fb.buffer_size,
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED,
                             fb.file_descriptor,
                             0);

    if ((int)fb.buffer == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(5);
    }

    return fb;
}

void set_pixel(struct frame_buffer fb,
               int x, int y,
               unsigned char r, unsigned char g, unsigned char b) {

    long int location = (x + y * fb.width) * (fb.var_info.bits_per_pixel / 8);

    *(fb.buffer + location + 0) = b;
    *(fb.buffer + location + 1) = g;
    *(fb.buffer + location + 2) = r;
    *(fb.buffer + location + 3) = 0;
}

void fill_rect(struct frame_buffer fb,
               int start_x, int start_y, int end_x, int end_y,
               unsigned char r, unsigned char g, unsigned char b) {
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            set_pixel(fb, x, y, r, g, b);
        }
    }
}


void flush_frame_buffer(struct frame_buffer fb) {
    //flush(fb.file_descriptor);
}

void destroy_frame_buffer(struct frame_buffer fb) {
    munmap(fb.buffer, fb.buffer_size);
    close(fb.file_descriptor);
}
