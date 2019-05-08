// Solution 1b
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto ans = numeric_limits<int>::min(); 
   for (auto a : v) { 
      for (auto b : v) { 
         ans = max(ans, abs(a - b)); 
      } 
   } 
   return ans; 
} 
