
// https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=d5c0c39547999033b2f58b9197208871

fn add<T: std::ops::Add<Output = T>>(a: T, b: T) -> T { a + b }
// fn add<T>(a: T, b: T) -> T { a + b } // fails

fn main() {
    println!("{}\n", add(1, 2));
}
