auto min_value(vector<int>& c) { 
   sort(begin(c), end(c)); 
   return transform_reduce(++cbegin(c), cend(c), cbegin(c), 
      numeric_limits<int>::max(), 
      [](auto a, auto b) { return min(a, b); }, 
      std::minus{}); 
} 
