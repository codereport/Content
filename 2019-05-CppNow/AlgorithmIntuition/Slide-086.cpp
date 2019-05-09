auto min_value(vector<int>& c) -> int { 
   sort(begin(c), end(c)); 
   vector<int> d(v.size ()); 
   adjacent_difference(cbegin(c), cend(c), begin(d)); 
   return *min_element(cbegin(d) + 1, cend(d)); 
} 
