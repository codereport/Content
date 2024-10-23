fn rmmmi(n: i32) -> i32 {
    (1..n)
        .map(|x| x % 10)
        .map(|x| x * 2)
        .map(|x| x + 1)
        .sum()
}

pub fn main() {
    let n = 100001;
    print!("{}", rmmmi(n));
}
