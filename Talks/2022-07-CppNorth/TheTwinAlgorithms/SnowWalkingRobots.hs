-- Solution 1 (using outerProduct)
import Data.List.HT (outerProduct)

countLRUD = map (sum . map fromEnum) 
          . outerProduct (==) "LRUD"

countLRUD "LRDLURDLURDULR" -- [4,4,3,3]

-- Solution 2 (using count)

import Data.List.Unique (count)

countLRUD = map snd . count

countLRUD "LRDLURDLURDULR" --[3,4,4,3]
