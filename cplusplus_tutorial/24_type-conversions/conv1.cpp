#include <cstdio>

class A {};

class B {
  public:
    // single-argument constructor that converts from A
    B(const A& a)
    {
      printf("B constructor called\n");
    }
    // assignment operator conversion from A
    B& operator=(const A& a)  // return value is B reference; argument is const reference to A
    {                         // return *this; return dereferenced pointer current B object
      printf("B assignment operator = called\n");
      return *this;
    }
                       
    // type-cast operator from A
    operator A()
    {
      printf("B type-cast operator A() called\n");
      return A();
    }
};

int main()
{
  A a;
  B b = a; // calls constructor
  b = a;   // calls assignment operator
  a = b;   // calls type-cast operator
}
