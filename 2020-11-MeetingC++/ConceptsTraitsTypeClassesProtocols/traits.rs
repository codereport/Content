
// https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=047a1b43fcf33a14f85015ff97e7302f

use core::f32::consts::PI;

trait Shape {
    fn name(&self)      -> String;
    fn area(&self)      -> f32;
    fn perimeter(&self) -> f32;
}

struct Circle    { r: f32 }
struct Rectangle { w: f32 h: f32 }

impl Shape for Circle {
    fn name(&self)      -> String { "Circle".to_string() }
    fn area(&self)      -> f32    { PI * self.r * self.r }
    fn perimeter(&self) -> f32    { 2.0 * PI * self.r }
}

impl Shape for Rectangle {
    fn name(&self)      -> String { "Rectangle".to_string() }
    fn area(&self)      -> f32    { self.w * self.h }
    fn perimeter(&self) -> f32    { 2.0 * self.w + 2.0 * self.h }
}

fn print_shape_info<T: Shape>(s: T) { 
    println!("Shape: {}\nArea:  {}\nPerim: {}\n", 
        s.name(), s.area(), s.perimeter());
}

fn main() {

    let c = Circle { r: 1.0 };
    let r = Rectangle { w: 2.0, h: 3.0 };

    print_shape_info(c);
    print_shape_info(r);
    
}
