#include <cppitertools/zip.hpp>

#include <vector>
#include <string>
#include <iostream>

template<class T>
void print_zipped(const std::initializer_list<int>&);

int main() {
    std::vector<int> ivec{1, 4, 9, 16, 25, 36};
    std::vector<std::string> svec{"hello", "good day", "goodbye"};

    std::cout << "zipping a vector of ints and a vector of strings\n";
    for (auto&& e : iter::zip(ivec, svec)) {
        std::cout << '(' << std::get<0>(e) << ", " << std::get<1>(e) << ")\n";
    }

    const std::vector<int> cvec{1, 4, 9, 16, 25, 36};

    std::cout << "zipping a vector of ints and a const vector of ints\n";
    for (auto&& e : iter::zip(ivec, cvec)) {
        std::cout << '(' << std::get<0>(e) << ", " << std::get<1>(e) << ")\n";
    }

    auto lst = {1, 4, 9, 16, 25, 36};
    const std::initializer_list<int>& rvec = lst;

    std::cout << "zipping a vector of ints and a const reference vector of ints\n";
    for (auto&& e : iter::zip(ivec, rvec)) {
        std::cout << '(' << std::get<0>(e) << ", " << std::get<1>(e) << ")\n";
    }

    print_zipped<float>({1, 4, 9, 16, 25, 36});
}


// implementation of print_zipped
template<class T>
void print_zipped(const std::initializer_list<int>& r)
{
  typename std::vector<T> l{1, 4, 9, 16, 25, 36};
  std::cout << "zipping const initializer list references passed as function arguments\n";
  for(auto&& e : iter::zip(r, l)) {
    std::cout << '(' << std::get<0>(e) << ", " << std::get<1>(e) << ")\n";
  }
}
