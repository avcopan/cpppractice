int main()
{
  int& a = 6; // ERROR
// error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
//    int& a = 6;
//             ^
}

// int& a requires a to be a reference to an lvalue -- one cannot create a reference to an rvalue like 6
