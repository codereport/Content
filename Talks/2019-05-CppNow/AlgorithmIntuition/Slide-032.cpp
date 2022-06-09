// Solution 3a 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto a = numeric_limits<int>::max(); 
   auto b = numeric_limits<int>::min(); 
   for (auto e : v) { 
      a = min(a, e); 
      b = max(b, e); 
   } 
   return b - a; 
} 
