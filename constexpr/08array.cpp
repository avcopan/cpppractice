#include <iostream>

template<typename T, size_t N>
class Array {
  private:
    constexpr static size_t _size = N;
    T _data[_size] {}; // T default constructor essential!
  public:
    constexpr size_t size()                       {  return         N;  }

    constexpr       T& operator[](size_t i)       {  return  _data[i];  }
    constexpr const T& operator[](size_t i) const {  return  _data[i];  }

    using const_iterator = const T*;
    constexpr const_iterator begin() const        {  return &_data[0];  }
    constexpr const_iterator end()   const        {  return &_data[N];  } // not N-1, since we want our stopping condition to be != <obj>.end()

    using iterator = T*;
    constexpr iterator       begin()              {  return &_data[0];  }
    constexpr iterator       end()                {  return &_data[N];  } // not N-1, since we want our stopping condition to be != <obj>.end()
};

template<typename T, size_t N>
constexpr Array<T, N> generate_range() {
  Array<T, N> ret;

  for (int i = 0; i < N; ++i) {
    T f = i;
    ret[i] = f;
  }

  return ret;
}


int main() {

  constexpr Array<double, 30> ran {generate_range<double, 30>()};

  for (Array<double, 30>::const_iterator it = ran.begin(); it != ran.end(); ++it)
    std::cout << *it << std::endl;
}
