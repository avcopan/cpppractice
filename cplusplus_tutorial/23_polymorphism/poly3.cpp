#include <cstdio>

// abstract base class definition -- an abstract base class is a class with pure virtual functions
// abstract base classes cannot be used to instantiate objects (i.e. Polygon p is invalid), but one
// can declare abstract base class pointers and assign them to the addresses of derived classes,
// which allows one to take advantage of polymorphism
// abstract base class pointers can be dereferenced, provided they refer to non-abstract derived classes
class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int wd, int ht) { width = wd; height = ht; }
    virtual int area() =0; // a "pure virtual function"
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

  printf("%d\n", ppoly1->area());
  printf("%d\n", ppoly2->area());
}
