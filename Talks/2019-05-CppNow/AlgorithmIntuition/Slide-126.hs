count_if f = length . filter f 
adj_diff   = mapAdjacent (-) 
  
count_adj_equals :: [Int] -> Int 
count_adj_equals = count_if (==0) . adj_diff 
