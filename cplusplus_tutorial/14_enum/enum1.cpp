#include <stdio.h>

enum color {black, blue, green, cyan, red, purple, yellow, white};

void print_color(color x)
{
  if     (x == black ) printf("color value: black \n");
  else if(x == blue  ) printf("color value: blue  \n");
  else if(x == green ) printf("color value: green \n");
  else if(x == cyan  ) printf("color value: cyan  \n");
  else if(x == red   ) printf("color value: red   \n");
  else if(x == purple) printf("color value: purple\n");
  else if(x == yellow) printf("color value: yellow\n");
  else if(x == white ) printf("color value: white \n");
}

int main()
{
  color c = red;
  print_color(c);
}
