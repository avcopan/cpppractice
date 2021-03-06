#include <vector>
#include <algorithm> // provides std::sort
#include <iostream>
#include <fstream>   // for streaming from files
#include "grader.hpp"

int main()
{
  std::vector<Student> students;
  Student student;

  std::ifstream in("students.txt");
  std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

  while(read(std::cin, student))
    students.push_back(student);

  std::sort(students.begin(), students.end());
  print_grades(students);
}
