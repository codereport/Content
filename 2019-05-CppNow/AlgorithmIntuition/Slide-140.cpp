auto solve() { 
   vector v = { 2, 1, 2, 4, 2, 3, 5, 2, 4, 7 }; 
   vector u(v.size(), 0); 
   inclusive_scan(cbegin(v), cend(v), begin(u), ufo::max{}); 
   return transform_reduce(cbegin(u), cend(u), cbegin(v), 0, 
      std::plus{}, 
      std::minus{}); 
} 
