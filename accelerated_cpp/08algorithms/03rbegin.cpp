#include <string>
#include <algorithm>
#include <iostream>

bool is_palindrome(const std::string& s) { return std::equal(s.begin(), s.end(), s.rbegin()); }

int main()
{
  std::cout << "Is it a palindrome?" << std::endl;
  std::string s1("madam");
  std::string s2("rotor");
  std::string s3("bilbo");
  std::string s4("bobbo");
  std::cout << s1 << ": " << (is_palindrome(s1) ? "yes" : "no") << std::endl;
  std::cout << s2 << ": " << (is_palindrome(s2) ? "yes" : "no") << std::endl;
  std::cout << s3 << ": " << (is_palindrome(s3) ? "yes" : "no") << std::endl;
  std::cout << s4 << ": " << (is_palindrome(s4) ? "yes" : "no") << std::endl;

  std::string s = "The quick brown fox jumps over the lazy dog";
  for(std::string::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
    std::cout << *it;
  std::cout << std::endl;

  std::copy(s.rbegin(), s.rend(), std::back_inserter(s));
  std::cout << s << std::endl;
}
