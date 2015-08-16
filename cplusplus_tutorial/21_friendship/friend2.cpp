#include <cstdio>

class Square;

class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle(int wd, int ht) : width(wd), height(ht) {}
    int area() { return width * height; }
    void init_from_square(Square square);
};

class Square {
    friend class Rectangle;
  private:
    int side;
  public:
    Square(int sd) : side(sd) {}
};

void Rectangle::init_from_square(Square square) {
  width = height = square.side;
}


int main()
{
  Rectangle rectangle;
  Square square(4);
  rectangle.init_from_square(square);
  printf("Rectangle area: %d\n", rectangle.area());
}
