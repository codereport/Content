template<class T> 
using rev = reverse_iterator<T>; 
  
int trap(vector<int>& v) { 
    vector u(v.size(), 0); 
    auto it = max_element(begin(v), end(v)); 
    inclusive_scan(begin(v),  next(it), begin(u),  ufo::max{}); 
    inclusive_scan(rbegin(v), rev(it),  rbegin(u), ufo::max{}); 
    return transform_reduce(cbegin(u), cend(u), cbegin(v), 0, 
        std::plus<>(), 
        std::minus<>()); 
} 
