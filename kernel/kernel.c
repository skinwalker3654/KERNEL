#define VIDEO_MEM ((unsigned short*)0xB8000)

#define MAX_HEIGHT 25
#define MAX_WIDTH 80

int current_width = 0;
int current_height = 0;

unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("inb %1, %0":"=a"(result):"d"(port));    
    return result;
}

void outb(unsigned short port, unsigned char value) {
    __asm__ volatile("outb %0, %1" :: "a"(value),"d"(port));    
}

void disable_cursor() {
    outb(0x3D4, 0x0A);  
    outb(0x3D5, 0x20);  
}

void screen_init() {
    for(int i=0; i<MAX_WIDTH*MAX_HEIGHT; i++) {
        VIDEO_MEM[i] = (0x0F << 8) | ' ';
    }

    disable_cursor();
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
        current_height++;
        current_width = 0;
    } else if(ch == '\b') {
        if(current_width > 0) {
            current_width--;
            VIDEO_MEM[current_height * MAX_WIDTH + current_width] = (0x0F << 8) | ' ';
        } else if(current_height > 0) {
            current_height--;
            current_width = MAX_WIDTH - 1;
            VIDEO_MEM[current_height * MAX_WIDTH + current_width] = (0x0F << 8) | ' ';
        }
    } else {
        if(current_width >= MAX_WIDTH) {
            current_height++;
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

char ascii_table[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
};

void keyboard_handler() {
    unsigned char scancode = inb(0x60);
    
    if(scancode < 0x80) {
        char key = ascii_table[scancode];
        if(key != 0) putchar(key);
    } 
    
    outb(0x20, 0x20);
}

void kernel_main() {
    screen_init();
    printk("Welcom to the OS!\n\n");
    while(1) {
        unsigned char status = inb(0x64);
        if(status & 0x01) {
            keyboard_handler();
        }
    }
}
