
class Shape a where
    name      :: a -> String
    area      :: a -> Float
    perimeter :: a -> Float

data Circle    = Circle {r :: Float}
data Rectangle = Rectangle {w :: Float, h :: Float}

instance Shape Circle where
    name      (Circle _) = "Circle"
    area      (Circle r) = pi * r ^ 2
    perimeter (Circle r) = 2 * pi * r

instance Shape Rectangle where
    name      (Rectangle _ _) = "Rectangle"
    area      (Rectangle w h) = w * h
    perimeter (Rectangle w h) = 2 * w + 2 * h

printShapeInfo :: Shape a => a -> IO()
printShapeInfo s = putStrLn ("Shape: " ++ (name s)           ++ "\n" ++ 
                             "Area:  " ++ show (area s)      ++ "\n" ++
                             "Perim: " ++ show (perimeter s) ++ "\n")

main :: IO ()
main = do
    printShapeInfo (Circle 1.0)
    printShapeInfo (Rectangle 2.0 3.0)
