#include "kernel.h"
#include "keyboard.h"

uint32 vga_index;
static uint32 next_line_index = 1;
uint8 g_fore_color = WHITE;
uint8 g_back_color = BLUE;


// Function to create a VGA buffer entry
uint16 vga_entry(char c, uint8 fore_color, uint8 back_color)
{
    return (back_color << 12) | (fore_color << 8) | c;
}

// Clear VGA buffer with given colors
void clear_vga_buffer(uint16 *buffer, uint8 fore_color, uint8 back_color)
{
    for (uint32 i = 0; i < BUFSIZE; i++) {
        buffer[i] = vga_entry(' ', fore_color, back_color);
    }
}

// Initialize VGA by setting up the buffer and clearing it
void init_vga(uint8 fore_color, uint8 back_color)
{
    vga_buffer = (uint16*) VGA_ADDRESS;
    clear_vga_buffer(vga_buffer, fore_color, back_color);
}

// Increase vga_index by width of row(80)
void print_new_line()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

//assign ascii character to video buffer
void putchar(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}


uint32 strlen(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}


//print string by calling putchar
void putstring(char *str)
{
  uint32 index = 0;
  while(str[index]){
    putchar(str[index]);
    index++;
  }
}



// I/O port functions from your code
uint8 inb(uint16 port) {
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outb(uint16 port, uint8 data) {
    asm volatile("outb %0, %1" : : "a"(data), "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

void test_input()
{
  char ch = 0;
  char keycode = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      print_new_line();
    }else{
      ch = get_ascii_char(keycode);
      putchar(ch);
    }
    sleep(0x022FFFFF);
  }while(ch > 0);
}

void kernel_main()
{
  //first init vga with fore & back colors
  init_vga(g_fore_color, g_back_color);
  putstring("Hello World!");
  print_new_line();
  putstring("Type here, one key per second");
  print_new_line();
  test_input();
}