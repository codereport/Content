-- Solution 1
isArraySpecial = foldl1 (&&)
               . ((zipWith (/=)) <*> tail)
               . map odd

-- Solution 2
import Data.List.HT (mapAdjacent)

isArraySpecial = foldl1 (&&)
               . mapAdjacent (/=)
               . map odd

-- Solution 3
import Data.List.HT (mapAdjacent)

isArraySpecial = and
               . mapAdjacent (/=)
               . map odd

-- Solution 3
import Data.List.HT (mapAdjacent)
import Data.Function (on)

isArraySpecial = and
               . mapAdjacent (on (/=) odd)
