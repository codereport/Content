import Data.List (sort)
import Data.Composition (.:)

sortString = map snd .: sort .: zip
