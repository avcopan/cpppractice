#include <iostream>

template <class T>
class MyClass {
  private:
    T value;
  public:
    MyClass(T val) { value = val; }
    T get_value() const { return value; }  // const-qualified to forbid the function from changing value
    void print_value() const { std::cout << value << std::endl; }
    template <class X> // member template, allowing us to use different template types
    void assign(const MyClass<X>& val) { value = val.get_value(); }
};

int main()
{
  MyClass<double> d(4.3);
  MyClass<int> i(5);

  d.print_value();
  i.print_value();

  d.assign(i);
  d.print_value();
}
