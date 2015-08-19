#include <iostream>

// a function that returns the maximum of two values:
template <class T>
inline const T& max (const T& a, const T& b) // *inline* functions get patched into the code wherever used upon compiling
{                                            // it sounds like the use of *inline* is for historical reasons and now no longer applicable
  return a > b ? a : b;
}


int main()
{
  std::cout << "max(  1,  2): " << max(  1,  2) << std::endl;
  std::cout << "max(114, 25): " << max(114, 25) << std::endl;
}
