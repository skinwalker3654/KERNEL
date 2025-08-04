#define VIDEO_MEM 0xB8000
#define HEIGHT 25
#define WIDTH 80

static unsigned char *video = (unsigned char*)VIDEO_MEM;
static int cursor = 0;

void clear_screen() {
    for(int i=0; i<WIDTH*HEIGHT*2; i+=2) {
        video[i] = ' ';
        video[i+1] = 0x07;
    }
}

void printk(const char *msg) {
    while(*msg) {
        video[cursor] = *msg;
        video[cursor+1] = 0x07;
        cursor += 2;
        msg++;
    }
}

void kernel_main() {
    clear_screen();
    printk("Hello, Kernel!");
    while(1) {}
}
