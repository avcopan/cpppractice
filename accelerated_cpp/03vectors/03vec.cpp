#include <iostream>
#include <vector>
#include <algorithm> // supplies std::sort
#include <stdexcept> // provides std::domain_error

double median(std::vector<double> v)
{
  std::vector<double>::size_type n = v.size();
  if(n == 0) throw std::domain_error("Cannot determine median of an empty vector.");
  std::sort(v.begin(), v.end()); // C++ std requires std::sort() to be no worse than N log(N) scaling
  return n % 2 == 0 ? (v[n/2] + v[n/2-1]) / 2 : v[n/2];
}

double grade(double midterm, double finalexam, const std::vector<double>& homeworks)
{
  return 0.2 * midterm + 0.4 * finalexam + 0.4 * median(homeworks);
}

int main()
{
  std::cout << "Midterm    grade: "; double midterm  ; std::cin >> midterm  ;
  std::cout << "Final exam grade: "; double finalexam; std::cin >> finalexam;
  std::cout << "Homework  grades: "; std::vector<double> homeworks; double homework;
  while(std::cin >> homework) homeworks.push_back(homework);

  std::cout << "Final grade: " << grade(midterm, finalexam, homeworks) << std::endl;
}
