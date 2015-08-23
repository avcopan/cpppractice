#include "grader.hpp"
#include <iostream>
#include <stdexcept>

bool operator<(const Student& lstudent, const Student& rstudent)
{
  return lstudent.name < rstudent.name;
}

double median(std::vector<double> v)
{
  std::vector<double>::size_type n = v.size();
  if(n == 0) throw std::domain_error("Cannot determine median of an empty vector.");
  std::sort(v.begin(), v.end());
  return n % 2 == 0 ? (v[n/2] + v[n/2-1]) / 2 : v[n/2];
}

std::istream& read_homeworks(std::istream& cin, std::vector<double>& homeworks)
{
  if(cin)
  {
    homeworks.clear();
    double homework;
    while(cin >> homework) homeworks.push_back(homework);
    cin.clear();
  }
  return cin;
}

std::istream& read(std::istream& is, Student& student)
{
  is >> student.name >> student.miderm >> student.finalexam;
  read_homeworks(is, student.homeworks);

  return is;
}

double grade(const Student& student)
{
  return 0.2 * student.midterm + 0.4 * student.finalexam + 0.4 * median(student.homeworks);
}

