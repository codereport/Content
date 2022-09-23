// Godbolt: https://godbolt.org/z/K6Yv8TKxv

pub fn filter_odds(list: Vec<i32>) -> Vec<i32> {
    list.into_iter()
        .filter(|e| e % 2 == 1)
        .collect()
}

pub fn sum_first_two_odds(list: Vec<i32>) -> i32 {
    list.into_iter()
        .filter(|e| e % 2 == 1)
        .take(2)
        .sum()
}

pub fn main() {

    println!("{:?}", filter_odds(vec![1,2,3,4,5]));
    println!("{:?}", sum_first_two_odds(vec![1,2,3,4,5]));

}
