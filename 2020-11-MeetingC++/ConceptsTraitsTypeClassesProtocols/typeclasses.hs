
-- originally failing

data Circle    = Circle {r :: Float}
data Rectangle = Rectangle {w :: Float, h :: Float}

name :: Circle -> String
name (Circle _) = "Circle"

area :: Circle -> Float
area (Circle r) = pi * r ^ 2

perimeter :: Circle -> Float
perimeter (Circle r) = 2 * pi * r

name :: Rectangle -> String
name (Rectangle _ _) = "Rectangle"

area :: Rectangle -> Float
area (Rectangle w h) = w * h

perimeter :: Rectangle -> Float
perimeter (Rectangle w h) = 2 * w + 2 * h

-- originally working

data Circle    = Circle {r :: Float}
data Rectangle = Rectangle {w :: Float, h :: Float}

circleName :: Circle -> String
circleName (Circle _) = "Circle"

circleArea :: Circle -> Float
circleArea (Circle r) = pi * r ^ 2

circlePerimeter :: Circle -> Float
circlePerimeter (Circle r) = 2 * pi * r

rectangleName :: Rectangle -> String
rectangleName (Rectangle _ _) = "Rectangle"

rectangleArea :: Rectangle -> Float
rectangleArea (Rectangle w h) = w * h

rectanglePerimeter :: Rectangle -> Float
rectanglePerimeter (Rectangle w h) = 2 * w + 2 * h

-- final

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
