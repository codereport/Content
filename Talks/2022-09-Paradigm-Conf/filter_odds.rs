// Godbolt: https://godbolt.org/z/ds7KGoWjv

pub fn filter_odds(list: Vec<i32>) -> Vec<i32> {
    list.into_iter()
        .filter(|e| e % 2 == 1)
        .collect()
}

pub fn main() {

    let vec = vec![1,2,3,4,5];

    println!("{:?}", filter_odds(vec));

}
