
// https://play.golang.org/p/sVr4ya1x58k

package main

import (
    "fmt"
    "math"
)

func main() {
    var a, b int = 1, 2
    var c = math.Min(a, b) // FAIL: cannot use a (type int) as type float64 in argument to math.Min
    fmt.Println(a + b)
}
