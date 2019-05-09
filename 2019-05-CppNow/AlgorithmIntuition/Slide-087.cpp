auto min_value(vector<int>& c) -> int { 
   sort(begin(c), end(c)); 
   return reduce(cbegin(c) + 1, cend(c), numeric_limits<int>::max(), 
      [prev = c.front()](auto a, auto b) mutable { 
      auto d = b - prev; 
      prev = b; 
      return min(a, d); 
   }); 
} 
