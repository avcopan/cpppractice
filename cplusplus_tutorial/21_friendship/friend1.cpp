#include <cstdio>

class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle(int wd, int ht) : width(wd), height(ht) {}
    int area() const { return width * height; }
    friend Rectangle duplicate(const Rectangle&);
    friend void print_properties(const Rectangle&);
};

// friend functions: note that they have access to the private attributes of the Rectangle class
// note that since we pass the argument as a const rectangle object, we can only call const members
// of the class on them -- that's why I qualified the area() method as a const member above
Rectangle duplicate(const Rectangle& rectangle)
{
  Rectangle newrectangle;
  newrectangle.width  = rectangle.width  * 2;
  newrectangle.height = rectangle.height * 2;
  return newrectangle;
}

void print_properties(const Rectangle& rectangle)
{
  printf("Rectangle properties: width %2d, height %2d, area %3d\n", rectangle.width, rectangle.height, rectangle.area());
}

int main()
{
  Rectangle smallrectangle(2,3);
  Rectangle bigrectangle = duplicate(smallrectangle);
  print_properties(smallrectangle);
  print_properties(bigrectangle);
}
