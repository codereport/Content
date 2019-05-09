   vector v = { 1, 2, 3 }; 
   vector u = { 2, 3, 4 }; 
  
   auto x = transform_reduce(cbegin(v), cend(v), cbegin(u), 0); 
   auto y = transform_reduce(cbegin(v), cend(v), cbegin(u), 0, plus{}, multiplies{}); 
   auto z = transform_reduce(cbegin(v), cend(v), cbegin(u), 0, 
      [](auto a, auto b) { return max(a, b); }, 
      [](auto a, auto b) { return a + b * b; }); 
