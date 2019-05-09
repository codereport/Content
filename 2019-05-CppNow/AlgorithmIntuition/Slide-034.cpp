// Solution 3c (C++20 Ranges) 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto a = *min_element(v); 
   auto b = *max_element(v); 
   return b - a; 
} 
