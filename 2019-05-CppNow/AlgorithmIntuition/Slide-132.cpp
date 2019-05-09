vector v = { 1, 1, 1, 1, 1 }; 
vector u(5, 0); 
partial_sum(cbegin(v), cend(v), begin(u)); 
  
// 1 2 3 4 5 
  
vector v = { 1, 2, 3, 4, 5 }; 
vector u(5, 0); 
partial_sum(cbegin(v), cend(v), begin(u)); 
  
// 1 3 6 10 15 
