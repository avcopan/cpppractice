#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <string>

class Base {
  public:
    virtual ~Base() {};
    virtual void test() { std::cout << "Base::test()" << std::endl; }
};

class Derived : public Base {
  public:
    virtual void test() { std::cout << "Derived::test()" << std::endl; }
};


int main()
{
  boost::tuple<int,std::string,Derived> tup1(-5, "tup1");
  boost::tuple<unsigned int,std::string,Base> tup2;

  tup2 = tup1; // int and Derived types can be cast to unsigned int and Base types, so this assignment is syntactically valid (though practically useless)

  tup2.get<2>().test(); // this calls Base::test(), not Derived::test() -- the Derived component has been "sliced",
                        // i.e. it has lost the information of the Derived class upon casting to Base
  std::cout << "Interesting value: " << tup2.get<0>() << std::endl; // casting negative int to unsigned int causes wrap-around -- you get a crazy high number

  const boost::tuple<double,std::string,Base> tup3(tup2);
//tup3.get<0>() = 3.14; // tup3 is const, so get returns const double& and this line throws a compile-time error

  Derived d;
  boost::tuple<int,std::string,Derived*> tup4(-4,"tup4",&d);
  boost::tuple<unsigned int,std::string,Base*> tup5;

  tup5 = tup4;

  tup5.get<2>()->test();

  boost::tuple<int,std::string,Derived&> tup6(12,"tup6",d);

  boost::tuple<unsigned int,std::string,Base&> tup7(tup6);

  tup7.get<2>().test();
}
