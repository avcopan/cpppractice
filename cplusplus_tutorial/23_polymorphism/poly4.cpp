#include <cstdio>

// illustrating the use of an abstract base class to define functions
// common to all derived classes
class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int wd, int ht) { width = wd; height = ht; }
    virtual int area() =0; // a "pure virtual function"
    void print_area() { printf("Area: %d\n", this->area()); }
};

class Rectangle : public Polygon {
  public:
    int area() { return width * height; }
};

class Triangle : public Polygon {
  public:
    int area() { return width * height / 2; }
};


int main()
{
  Rectangle rectangle;
  Triangle  triangle;

  Polygon* ppoly1 = &rectangle;
  Polygon* ppoly2 = &triangle;

  ppoly1->set_values(4, 5);
  ppoly2->set_values(4, 5);

  ppoly1->print_area();
  ppoly2->print_area();
}
