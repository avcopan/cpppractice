#include <string>
#include <vector>
#include <algorithm> // provides std::max
#include <iostream>
#include <iomanip>

int main()
{
  std::vector<Student> students;
  Student student;
  std::string::size_type maxlen = 0;

  while(read(std::cin, student))
  {
    maxlen = std::max(maxlen, student.name.size());
    students.push_back(student);
  }

  sort(students.begin(), students.end());

  std::streamsize prec;
  for(std::vector<Student>::size_type i = 0; i != students.size(); ++i)
    std::cout << std::setw(maxlen + 1)   << students[i].name
              << std::setprecision(3)    << grade(students[i])
              << std::setprecision(prec) << std::endl;
}
