min_value :: [Int] -> Int 
min_value = minimum . mapAdjacent (flip (-)) . sort 
