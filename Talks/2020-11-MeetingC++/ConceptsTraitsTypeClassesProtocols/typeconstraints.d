
// https://run.dlang.io/is/H3BqLg
// https://www.godbolt.org/z/9fsfnx

import std.stdio;
import std.string;
import std.math;

template shape(T) {
    const shape = __traits(compiles, (T t) { 
        t.name();
    	t.area();
    	t.perimeter();
    });
}

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

void printShapeInfo(T)(T s) 
    if (shape!(T)) 
{
   writeln("Shape: ",   s.name(), 
           "\nArea:  ", s.area(), 
           "\nPerim: ", s.perimeter(), "\n");   
}

void main() {

    auto c = new const Circle(1);
    auto r = new const Rectangle(2, 3);
    
    printShapeInfo(c);
    printShapeInfo(r);
}
