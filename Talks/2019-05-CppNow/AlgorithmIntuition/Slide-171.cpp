auto generate_n_fibonacci(int n) { 
   vector fib(n, 1); 
   adjacent_difference(cbegin(fib), 
                       cend  (fib) - 1, 
                       begin (fib) + 1, 
                       std::plus{}); 
   return fib; 
} 
