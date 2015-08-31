#include <boost/operators.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>
#include <set>
#include <algorithm> // provides std::for_each and std::find

class Animal : boost::less_than_comparable<Animal, boost::equality_comparable<Animal> > {
  private:
    std::string name_;
    int age_;
  public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}
    void print() const { std::cout << name_ << " with the age " << age_ << std::endl; }
    // I think this new definition of operator< will result in proper functionality -- use age as tie-breaker when names are the same
    friend bool operator< (const Animal& lhs, const Animal& rhs) { return lhs.name_ == rhs.name_ ? (lhs.age_ < rhs.age_) : (lhs.name_ < rhs.name_); }
    friend bool operator==(const Animal& lhs, const Animal& rhs) { return lhs.name_ == rhs.name_ && lhs.age_ == rhs.age_; }
};


int main()
{
  Animal a1("Monkey",   3);
  Animal a2("Bear"  ,   8);
  Animal a3("Turtle",  56);
  Animal a4("Monkey", 200);

  std::set<Animal> s;
  s.insert(a1);
  s.insert(a2);
  s.insert(a3);
  s.insert(a4);

  std::cout << "Number of animals: " << s.size() << std::endl;
  std::for_each(s.begin(), s.end(), boost::bind(&Animal::print, _1));
  std::cout << std::endl;

  std::set<Animal>::iterator it(s.find(Animal("Monkey", 200)));
  if (it != s.end()) { std::cout << "We found the 200 year old monkey!" << std::endl; it->print(); } // Animal("Monkey", 3) as a match

  it = std::find(s.begin(), s.end(), Animal("Monkey", 200));
  if (it == s.end()) { std::cout << "No 200 year old monkey could be find in this set." << std::endl; }
}
