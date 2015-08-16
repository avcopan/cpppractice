#include <cstdio>

// base class
// note that here the attributes are *protected* rather than *private* -- the difference between private
// and protected attributes is that derived classes have access to the latter (not the former)
// neither private nor protected attributes can be accessed in main()
class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int wd, int ht) { width=wd; height=ht; }
};

// derived classes -- this is an example of ``public inheritance'', which allows us to access
// Polygon's public function set_values() as a public function of Rectangle and Triangle in main()
// if we set the inheritance to ``protected'', set_values() would be accessible by derived classes
// of Rectangle and Triangle but would not be accessible in main()
// if we set the inheritance to ``private'', the protected and public members of Polygon would be
// accessible only within Rectangle/Triangle or its friends
//
// ______ACCESS______|__public__|__protected__|_private__
// members, friends  |    y     |      y      |    y
// derived classes   |    y     |      y      |
// non-members       |    y     |             |
class Rectangle : public Polygon {
  public:
    int area() { return width * height; }
};

class Triangle  : public Polygon {
  public:
    int area() { return width * height / 2; }
};


int main()
{
  Rectangle rectangle;
  Triangle  triangle;

  rectangle.set_values(4, 5);
  triangle.set_values(4, 5);

  printf("Rectangle area: %d\n", rectangle.area());
  printf("Triangle  area: %d\n", triangle.area());
}
