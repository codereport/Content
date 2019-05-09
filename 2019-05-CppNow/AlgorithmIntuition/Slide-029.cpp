// Solution 2a 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   sort(begin(v), end(v)); 
   return *--end(v) - *begin(v); 
} 
