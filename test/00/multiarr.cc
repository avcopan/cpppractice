#include <iostream>
#include <vector>

class Dummy {
  public:
    Dummy();
    template<typename T>
    void func(T);
    template<typename T, typename... Args>
    void func(T, Args...);
};

Dummy::Dummy() { std::cout << "Called constructor." << std::endl; }

template<typename T>
void Dummy::func(T t) 
{
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void Dummy::func(T t, Args... args) // recursive variadic function
{
    std::cout << t << std::endl;

    func(args...);
}

int main()
{
  Dummy x;
  x.func(1,2,3,4,5,6);
}
