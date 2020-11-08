
-- add :: t -> t -> t
-- add a b = a + b

add :: Num t => t -> t -> t
add a b = a + b

main :: IO ()
main = do
    print $ add 1 2
