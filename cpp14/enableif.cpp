#include <iostream>
#include <type_traits>

// variadic function -- swallows anything that falls through the cracks during overload resolution
int func(...  ) {return 0;}

// function overload to capture calls with a single float argument
int func(float) {return 1;}

// templated function using std::enable_if to capture integral types (bool, int, char, ...)
template<typename T>
typename std::enable_if<std::is_integral<T>::value,int>::type func(T) {return 2;}
// this illustrates SFINAE:
//   If the first template argument of std::enable_if (type 'bool') is not satisfied
//   when 'type' is substituted for T, this generates a compile error inside the
//   template.  Rather than quitting upon encountering this *substitution failure*,
//   the compiler drops the template from the overload set that it's building.
//   ==> the acronym SFINAE (substitution failure is not an error)
/*
  reference:

    - std::enable_if

      - template<bool B, class T=void> struct enable_if {
          typedef T type; 
        };

      - If B is true, std::enable_if has a static member variable 'type' (of type 'typedef'), equal to T;
        otherwise, there is no member typedef. 

    - std::is_integral

      - template<class T> struct is_integral {
          static bool value;
        };

        template<class T> bool is_integral<T>::value = false;

      - provides static member bool 'value' which equals 'true' if T is in
          { bool, char,  char16_t, char32_t, wchar_t, short, int, long,
            long long, or any implementation-defined extended integer types,
            including any signed, unsigned, and cv-qualified variants. }
        and otherwise equals 'false'
*/

int main() {
  std::cout << "func(nullptr) -> " << func(nullptr) << std::endl;
  std::cout << "func(2      ) -> " << func(2      ) << std::endl;
  std::cout << "func(2,2,2,2) -> " << func(2,2,2,2) << std::endl;
  std::cout << "func(2.f    ) -> " << func(2.f    ) << std::endl;
  std::cout << "func(2.f,2.f) -> " << func(2.f,2.f) << std::endl;
  std::cout << "func('a'    ) -> " << func('a'    ) << std::endl;
  std::cout << "func(2.0    ) -> " << func(2.0    ) << std::endl;
  std::cout << "func(true   ) -> " << func(true   ) << std::endl;
}
