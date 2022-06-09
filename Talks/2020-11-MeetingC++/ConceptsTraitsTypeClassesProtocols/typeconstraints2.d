//https://run.dlang.io/is/oA2PSQ
import std.stdio, std.math, std.typecons : wrap;

class Circle {
    float r;
    this(float radius) { r = radius; }
    string name()      const { return "Circle"; }
    float  area()      const { return PI * r * r; }
    float  perimeter() const { return 2 * PI * r; }
}

class Rectangle {
    float w, h;
    this(float width, float height) { w = width; h = height; }
    string name()      const { return "Rectangle"; }
    float  area()      const { return w * h; }
    float  perimeter() const { return 2 * w + 2 * h; }
}

interface Shape {  // note how the classes above don't know anything about this interface
    string name()      const;
    float  area()      const;
    float  perimeter() const;
}

enum shape(alias x) = __traits(compiles, x.wrap!Shape);

void printShapeInfo(T)(T s) 
  if (shape!s) 
{
   writefln("Shape: %s\nArea:  %s\nPerim: %s\n", s.name(), s.area(), s.perimeter());   
}

void main() {
    auto c = new const Circle(1);
    auto r = new const Rectangle(2, 3);
    printShapeInfo(c);
    printShapeInfo(r);
}