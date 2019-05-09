auto count_adj_equals(vector<int> const& v) -> int { 
    vector d(v.size(), 0); 
    adjacent_difference(cbegin(v), cend(v), begin(d)); 
    return count_if(cbegin(d) + 1, cend(d), 
            [](auto e) { return e == 0; }); 
} 
