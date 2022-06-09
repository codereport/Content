   vector v = { 1, 2, 3 }; 
  
   auto x = accumulate(cbegin(v), cend(v), 0); 
   auto y = accumulate(cbegin(v), cend(v), 1, multiplies{}); 
