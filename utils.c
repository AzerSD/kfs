#include "kernel.h"

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

uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//print string by calling putchar
void putstr(char *str)
{
  uint32 index = 0;
  while(str[index]){
    putchar(str[index]);
    index++;
  }
}

//print int by converting it into string
//& then printing string
void putint(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  putstr(str_num);
}
