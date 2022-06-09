auto min_value(vector<int>& coins) -> int { 
   sort(begin(coins), end(coins)); 
   vector<int> diff(v.size ()); 
   adjacent_difference(cbegin(coins), cend(coins), begin (diff)); 
   return *min_element(cbegin(diff) + 1, cend(diff)); 
} 
