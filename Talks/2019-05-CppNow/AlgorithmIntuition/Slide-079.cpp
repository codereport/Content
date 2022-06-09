   vector v = { 1, 2, 3 }; 
  
   auto x =  my::any_of(cbegin(v), cend(v), [](auto e) { return e == 3; }); 
   auto y = std::any_of(cbegin(v), cend(v), [](auto e) { return e == 3; }); 
