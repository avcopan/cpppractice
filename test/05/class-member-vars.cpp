#include <iostream>

class Dummy {
  public:
    static int member_variable;
};

struct Dumbo {
  static int member_variable;
};

int Dummy::member_variable = 5;
int Dumbo::member_variable = 7;

int main() {
  Dumbo dumbo1;
  Dumbo dumbo2;
  Dummy dummy1;
  Dummy dummy2;

  std::cout << "Dummy::member_variable -> " << Dummy::member_variable << std::endl;
  std::cout << "dummy1.member_variable -> " << dummy1.member_variable << std::endl;
  std::cout << "dummy2.member_variable -> " << dummy2.member_variable << std::endl;
  std::cout << "Dumbo::member_variable -> " << Dumbo::member_variable << std::endl;
  std::cout << "dumbo1.member_variable -> " << dumbo1.member_variable << std::endl;
  std::cout << "dumbo2.member_variable -> " << dumbo2.member_variable << std::endl;

  Dummy::member_variable = 11; std::cout << "  Dummy::member_variable = 11;" << std::endl;
  dummy1.member_variable = 13; std::cout << "  dummy1.member_variable = 13;" << std::endl;
  dummy2.member_variable = 15; std::cout << "  dummy2.member_variable = 15;" << std::endl;

  Dumbo::member_variable = 17; std::cout << "  Dumbo::member_variable = 17;" << std::endl;
  dumbo1.member_variable = 19; std::cout << "  dumbo1.member_variable = 19;" << std::endl;
  dumbo2.member_variable = 21; std::cout << "  dumbo2.member_variable = 21;" << std::endl;

  std::cout << "Dummy::member_variable -> " << Dummy::member_variable << std::endl;
  std::cout << "dummy1.member_variable -> " << dummy1.member_variable << std::endl;
  std::cout << "dummy2.member_variable -> " << dummy2.member_variable << std::endl;
  std::cout << "Dumbo::member_variable -> " << Dumbo::member_variable << std::endl;
  std::cout << "dumbo1.member_variable -> " << dumbo1.member_variable << std::endl;
  std::cout << "dumbo2.member_variable -> " << dumbo2.member_variable << std::endl;
}
