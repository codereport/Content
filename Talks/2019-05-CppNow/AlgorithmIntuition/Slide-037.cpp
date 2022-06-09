// Solution 4c (C++20) 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto [a, b] = minmax_element(v); 
   return *b - *a; 
} 
