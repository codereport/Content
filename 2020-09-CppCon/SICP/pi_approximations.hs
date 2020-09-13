
pi n = sum 
     . take n 
     . map (4/) 
     $ zipWith (*) (cycle [1,-1]) [1,3..]
