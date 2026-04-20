#define VIDEO_MEM ((unsigned short*)0xB8000)

#define MAX_HEIGHT 25
#define MAX_WIDTH 80

int current_width = 0;
int current_height = 0;

void screen_init() {
    for(int i=0; i<MAX_WIDTH*MAX_HEIGHT; i++) {
        VIDEO_MEM[i] = (0x0F << 8) | ' ';
    }
}

void scroll(void) {
    for(int i=0; i<(MAX_HEIGHT-1)*MAX_WIDTH; i++) {
        VIDEO_MEM[i] = VIDEO_MEM[i + MAX_WIDTH];
    }

    for(int i=(MAX_HEIGHT-1)*MAX_WIDTH; i<MAX_HEIGHT*MAX_WIDTH; i++) {
        VIDEO_MEM[i] = (0x0F << 8) | ' ';
    }

    current_height = MAX_HEIGHT-1;
    current_width = 0;
}

void putchar(char ch) {
    if(ch == '\n') {
        current_height--;
        current_width = 0;
        current_width++;
    } else {
        if(current_width >= MAX_WIDTH) {
            current_height--;
            current_width = 0;
        }

        if(current_height >= MAX_HEIGHT) {
            scroll();
        }

        VIDEO_MEM[current_height * MAX_WIDTH + current_width] = (0x0F << 8) | ch;
        current_width++;
    }
}

void printk(char *message) {
    while(*message) {
        putchar(*message);
        message++;
    }
}

void kernel_main() {
    screen_init();
    printk("Hello, Kernel!");
    while(1);
}
