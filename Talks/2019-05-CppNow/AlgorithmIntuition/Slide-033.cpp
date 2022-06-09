// Solution 3b 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto a = *min_element(begin(v), end(v)); 
   auto b = *max_element(begin(v), end(v)); 
   return b - a; 
} 
