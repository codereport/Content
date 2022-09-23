fun filterOdds(lst: List<Int>): List<Int>
    = lst.filter{ x -> x % 2 != 0 }

fun sumFirstTwoOdds(lst: List<Int>): Int
    = lst.filter{ x -> x % 2 != 0 }
         .take(2)
         .sum()

fun main() {
    var list = listOf<Int>(1, 2, 3, 4, 5)
    println(filterOdds(list))
    println(sumFirstTwoOdds(list))
}
