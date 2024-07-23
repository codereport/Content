import Data.List (sortOn)
import Data.Composition (.:)

sortString = map snd .: sortOn fst .: zip
