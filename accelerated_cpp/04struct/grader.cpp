#include "grader.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
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
  is >> student.name >> student.midterm >> student.finalexam;
  read_homeworks(is, student.homeworks);

  return is;
}

double grade(const Student& student)
{
  return 0.2 * student.midterm + 0.4 * student.finalexam + 0.4 * median(student.homeworks);
}

std::vector<Student> extract_fails(std::vector<Student>& students)
{
  std::vector<Student> pass, fail;

  for(std::vector<Student>::size_type i = 0; i != students.size(); ++i)
  {
    if(grade(students[i]) < 60) fail.push_back(students[i]);
    else                        pass.push_back(students[i]);
  }

  students = pass;
  return fail;
}

void print_grades(const std::vector<Student>& students)
{
  std::string::size_type maxlen = 0;
  for(std::vector<Student>::size_type i = 0; i != students.size(); ++i)
    maxlen = std::max(maxlen, students[i].name.size());

  std::streamsize prec;
  for(std::vector<Student>::size_type i = 0; i != students.size(); ++i)
    std::cout << std::setw(maxlen + 1)   << std::left          << students[i].name
              << std::setprecision(3)    << grade(students[i])
              << std::setprecision(prec) << std::endl;

}

