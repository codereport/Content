// Solution 1a 
  
auto solve() -> int { 
   vector v = { 2, 1, 3, 5, 4 }; 
   auto ans = numeric_limits<int>::min(); 
   for (int i = 0; i < v.size(); ++i) { 
      for (int j = 0; j < v.size(); ++j) { 
         ans = max(ans, abs(v[i] - v[j])); 
      } 
   } 
   return ans; 
} 
