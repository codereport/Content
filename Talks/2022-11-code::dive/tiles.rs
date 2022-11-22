// https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=7b9582706c99ea749a7950e754bfaf7e

use itertools::Itertools;

pub fn main() {
    let tile_bag = vec!['A', 'B', 'B', 'B', 'C', 'C', 'D', 'E', 'F', 'F'];
    let tile_bag_index = 2;

    let tiles = tile_bag
        .iter()
        .skip(tile_bag_index)
        .counts()
        .iter()
        .sorted()
        .map(|(a, b)| format!("{a}:{b}"))
        .collect::<Vec<_>>()
        .join(" ");

    println!("{tiles}");
}
