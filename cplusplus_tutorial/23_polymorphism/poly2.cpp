#include<cstdio>

class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int wd, int ht) { width = wd; height = ht; }
    virtual int area () { return 0; } // virtual functions can be overwritten by derived classes
};                                    // these permit area() to be accessed via base class pointers

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
  Polygon   polygon;

  Polygon* ppoly1 = &rectangle;
  Polygon* ppoly2 = &triangle;
  Polygon* ppoly3 = &polygon;

  ppoly1->set_values(4, 5);
  ppoly2->set_values(4, 5);
  ppoly3->set_values(4, 5);

  printf("%d\n", ppoly1->area()); // this calls Rectangle::area()
  printf("%d\n", ppoly2->area()); // this calls  Triangle::area()
  printf("%d\n", ppoly3->area()); // this calls   Polygon::area()
  // without the keyword 'virtual' in front of the Polygon::area() declaration, all three of these
  // would have called the original Polygon::area() function and returned 0
}
