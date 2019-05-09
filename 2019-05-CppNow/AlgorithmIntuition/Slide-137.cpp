auto solve() { 
   vector v = { 2, 1, 2, 4, 2, 3, 5, 2, 4, 7 }; 
   auto m   = v.front(); // max so far 
   auto ans = 0; 
   for (auto e : v) { 
      m    = max(m, e); 
      ans += m - e; 
   } 
   return ans; 
} 
