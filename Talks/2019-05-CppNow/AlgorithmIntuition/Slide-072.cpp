   vector v = { 1, 2, 3 }; 
  
   auto x = reduce(cbegin(v), cend(v)); 
   auto y = reduce(cbegin(v), cend(v), 0, plus{}); 
   auto z = reduce(cbegin(v), cend(v), 1, multiplies{}); 
