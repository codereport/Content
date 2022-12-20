-- https://godbolt.org/z/5G36azaY7
-- 212 instructions with ghc 9.2.2 with -O2 (O3 is the same)

calculate :: Int -> Int -> Int
calculate bottom top = sum $ filter even [bottom..top]

main = do  
    print $ calculate 5 12 -- 36
    print $ calculate 5 3  -- 0
