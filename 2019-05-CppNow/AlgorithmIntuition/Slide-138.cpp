auto solve() { 
   vector v = { 2, 1, 2, 4, 2, 3, 5, 2, 4, 7 }; 
   vector u(v.size(), 0); 
   partial_sum(cbegin(v), cend(v), begin(u), 
      [](auto a, auto b) { return max(a, b); }); 
   return transform_reduce(cbegin(v), cend(v), cbegin(u), 0, 
      std::plus{}, 
      [](auto a, auto b) { return abs(a - b); }); 
} 
