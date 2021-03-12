
// func add(_ a: Int, _ b: Int) -> Int { a + b }
func add<T: Numeric>(_ a: T, _ b: T) -> T { a + b }
//func add<T>(_ a: T, _ b: T) -> T { a + b } // fails

print(add(1, 2))
