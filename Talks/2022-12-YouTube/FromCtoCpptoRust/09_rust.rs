// https://godbolt.org/z/3ffcMPncz
// 50 instructions with rustc 1.65.0 -C opt-level=3
// 50 instructions with rustc 1.65.0 -C opt-level=2

fn calculate(bottom: i32, top: i32) -> i32 {
    (bottom..=top).filter(|e| e % 2 == 0).sum()
}

pub fn main() {
    println!("{}", calculate(5, 12)); // 36
    println!("{}", calculate(5, 3)); // 0
}
