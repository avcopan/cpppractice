#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

struct movie { std::string title; int year; };

int main()
{
  movie   m;
  movie* pm = &m; // declare pm as pointer to m of type 'movie'

  std::cout << "Enter title: ";
  std::getline(std::cin, pm->title);
  std::cout << "Enter year: ";
  std::string str_input;
  std::getline(std::cin, str_input);
  std::stringstream(str_input) >> pm->year;

  printf("\nYou have enetered:\n%s (%d)\n", m.title.c_str(), m.year);
}
