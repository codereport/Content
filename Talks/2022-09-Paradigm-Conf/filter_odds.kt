fun filterOdds(lst: List<Int>): List<Int>
    = lst.filter{ x -> x % 2 != 0 }


fun main() {
    var list = listOf<Int>(1, 2, 3, 4, 5)
    println(filterOdds(list))
}