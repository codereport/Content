filterOdds xs  = filter odd xs
filterOdds1    = filter odd
filterOdds2    = filter (\e -> (mod e 2) == 1)
filterOdds3 xs = [ x | x <- xs, odd x ]

main :: IO ()
main = do
    print $ filterOdds  [1..5]
    print $ filterOdds1 [1..5]
    print $ filterOdds2 [1..5]
    print $ filterOdds3 [1..5]
