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

int main()
{
  std::cout << "Midterm    grade: "; double midterm  ; std::cin >> midterm  ;
  std::cout << "Final exam grade: "; double finalexam; std::cin >> finalexam;
  std::cout << "Homework  grades: "; std::vector<double> homeworks;
  if(read_homeworks(std::cin, homeworks))
    std::cout << "Successfully read in homeworks" << std::endl;

  std::cout << "Final grade: " << grade(midterm, finalexam, homeworks) << std::endl;
}
