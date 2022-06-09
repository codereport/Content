// Solution 4a 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto p = minmax_element(cbegin(v), cend(v)); 
   return *p.second - *p.first; 
} 
