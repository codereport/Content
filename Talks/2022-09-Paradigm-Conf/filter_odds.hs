filterOdds xs = filter odd xs
filterOdds1   = filter odd

main :: IO ()
main = do
    print $ filterOdds [1..5]
