#include <boost/bind.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class PersonalInfo {
  private:
    std::string name_;
    std::string surname_;
    unsigned int age_;
  public:
    PersonalInfo(const std::string& name, const std::string& surname, unsigned int age) : name_(name), surname_(surname), age_(age) {}

    std::string  name()    const { return name_;    }
    std::string  surname() const { return surname_; }
    unsigned int age()     const { return age_;     }
};

std::ostream& operator<<(std::ostream& lhs, const PersonalInfo& rhs)
{
  lhs << rhs.name() << ' ' << rhs.surname() << ", age " << rhs.age() << std::endl;
  return lhs;
}

int main()
{
  std::vector<PersonalInfo> v;
  v.push_back(PersonalInfo("Little", "John", 31));
  v.push_back(PersonalInfo("Friar" , "Tuck", 52));
  v.push_back(PersonalInfo("Robin" , "Hood", 39));

  // sort by age
  // boost::bound std::less, acting on age return values, which are themselves gotten by boost::bound PersonalInfo::age method
  std::sort(v.begin(), v.end(), boost::bind(std::less<unsigned int>(),boost::bind(&PersonalInfo::age,_1),boost::bind(&PersonalInfo::age,_2)));
  std::cout << std::endl << "PersonalInfos sorted by age:" << std::endl;
  std::cout << v[0] << v[1] << v[2];

  // sort by name
  std::sort(v.begin(), v.end(), boost::bind(std::less<std::string>(),boost::bind(&PersonalInfo::name,_1),boost::bind(&PersonalInfo::name,_2)));
  std::cout << std::endl << "PersonalInfos sorted by name:" << std::endl;
  std::cout << v[0] << v[1] << v[2];

  // sort by surname
  std::sort(v.begin(), v.end(), boost::bind(std::less<std::string>(),boost::bind(&PersonalInfo::surname,_1),boost::bind(&PersonalInfo::surname,_2)));
  std::cout << std::endl << "PersonalInfos sorted by surname:" << std::endl;
  std::cout << v[0] << v[1] << v[2];
}
