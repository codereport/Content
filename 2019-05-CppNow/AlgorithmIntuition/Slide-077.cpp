   vector v = { 1, 2, 3, 1, 2 }; 
  
   auto x =  my::count(cbegin(v), cend(v), 1); 
   auto y = std::count(cbegin(v), cend(v), 1); 
