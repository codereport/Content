   // map<int, int> queries; 
  
   vector v = { 1, 2, ... , 100 }; 
   vector u(v.size(), 0); 
   partial_sum(cbegin(v), cend(v), begin(u)); 
  
   for (auto [a, b] : queries) { 
      auto sum = u[b] - u[a]; 
   } 
