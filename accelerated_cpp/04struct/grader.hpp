#ifndef GUARD_grader_hpp  // if GUARD_grader_hpp is defined, this skips to #endif below -- otherwise it goes to the next line
#define GUARD_grader_hpp  // GUARD_grader_hpp was undefined; now we define it -- future inclusion of this file will skip the contents

#include <vector>
#include <string>
#include <iostream>

struct Student {
  std::string name;
  double midterm, finalexam;
  std::vector<double> homeworks;
};

bool operator<(const Student&, const Student&);

double median(std::vector<double>);

double grade(const Student&);

std::istream& read_homeworks(std::istream&, std::vector<double>&);

std::istream& read(std::istream&, Student&);

std::vector<Student> extract_fails(std::vector<Student>&);

void print_grades(const std::vector<Student>&);

#endif
