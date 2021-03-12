
// https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=0a3c8942297fd09aba64f869dcbebf62

// fn add(a: i32, b: i32) -> i32 { a + b }
fn add<T: std::ops::Add<Output = T>>(a: T, b: T) -> T { a + b }
// fn add<T>(a: T, b: T) -> T { a + b } // fails

fn main() {
    println!("{}\n", add(1, 2));
}
