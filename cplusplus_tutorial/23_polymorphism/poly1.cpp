#include <cstdio>

class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int wd, int ht) { width=wd; height=ht; }
};

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
  Polygon* ppoly1 = &rectangle;
  Polygon* ppoly2 = &triangle;

  ppoly1->set_values(4, 5); // equivalent to rectangle.set_values(4, 5);
  ppoly2->set_values(4, 5); // equivalent to  triangle.set_values(4, 5);

  printf("%d\n", rectangle.area()); // ppoly1->area() will not work, because ppoly1 has type pointer to Polygon -- only members inherited from
  printf("%d\n", triangle.area());  // Polygon will be accessible to it
}
