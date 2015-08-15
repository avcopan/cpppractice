#include <stdio.h>

struct product {
  int weight;
  double price;
};

void print_product(product p)
{
  printf("product weight: %d\n", p.weight);
  printf("product price : %f\n", p.price );
}

int main()
{
  product apple;
  product banana;
  product melon;

  apple.weight = 2;
  banana.weight = 3;
  melon.weight = 4;

  apple.price = 1.2;
  banana.price =  2.3;
  melon.price = 1.8;

  printf("apple:\n");
  print_product(apple);
  printf("banana:\n");
  print_product(banana);
  printf("melon:\n");
  print_product(melon);

  // alternatively, the struct definition and variable declaration can be done simultaneously:
  struct prod { int weight; double price; } bananana;
  bananana.weight = 3;
  bananana.price  = 2.3;
  printf("bananana:\n");
  printf("prod weight: %d\n", bananana.weight);
  printf("prod price : %f\n", bananana.price );
}
