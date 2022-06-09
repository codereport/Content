// Solution 4b 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto [a, b] = minmax_element(begin(v), end(v)); 
   return *b - *a; 
} 
