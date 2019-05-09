   vector v = { 1, 2, 3 }; 
  
   auto x = reduce(cbegin(v), cend(v), 0, 
      [](auto a, auto b) { return a + b * b; }); 
  
   auto y = transform_reduce(cbegin(v), cend(v), 0, 
      std::plus{}, 
      [](auto e) { return e * e; }); 
