#include <cstdio>

class Polygon {
  protected:
    int width, height;
  public:
    Polygon(int wd, int ht) : width(wd), height(ht) {}
    virtual int area() =0;
    void print_area() { printf("Area: %d\n", this->area()); }
};

class Rectangle : public Polygon {
  public:
    Rectangle(int wd, int ht) : Polygon(wd, ht) {}
    int area() { return width * height; }
};

class Triangle  : public Polygon {
  public:
    Triangle(int wd, int ht) : Polygon(wd, ht) {}
    int area() { return width * height / 2; }
};


int main()
{
  Polygon* ppoly1 = new Rectangle(4, 5);
  Polygon* ppoly2 = new Triangle(4, 5);

  ppoly1->print_area();
  ppoly2->print_area();

  delete ppoly1;
  delete ppoly2;
}
