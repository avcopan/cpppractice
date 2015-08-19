#include <algorithm>
#include <iostream>
#include <iomanip>

// using std::swap -- in C++11 this belongs to <utility> instead of <algorithm>
void reverse_array_simple(int* arr, int n)
{
  int first = 0, last = n - 1;
  while(first < last)
  {
    std::swap(arr[first], arr[last]);
    first++; last--;
  }
}

// using pointers
void reverse_array(int* arr, int n)
{
  int* first = arr;
  int* last = arr + n - 1;
  int tmp;
  while(first < last)
  {
    tmp = *last;
    *last = *first;
    *first = tmp;
    first++; last--;
  }
}

void print_array(int* arr, int n)
{
  std::cout << "[";
  for(int i = 0; i < n; ++i) std::cout << std::setw(3) << arr[i];
  std::cout << "]\n";
}

int main()
{
  int* arr1 = new int[10];
  int* arr2 = new int[10];
  for(int i = 0; i < 10; ++i)
    arr1[i] = arr2[i] = i;

  print_array(arr1, 10);
  print_array(arr2, 10);
  reverse_array_simple(arr1, 10);
  reverse_array(arr2, 10);
  print_array(arr1, 10);
  print_array(arr2, 10);

  delete[] arr1;
  delete[] arr2;
}
