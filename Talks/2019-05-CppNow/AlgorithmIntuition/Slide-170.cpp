auto generate_n_fibonacci(int n) { 
   vector fib(n, 1); 
   transform(cbegin(fib), 
             cend  (fib) - 2, 
             cbegin(fib) + 1, 
             begin (fib) + 2, 
             std::plus{}); 
   return fib; 
} 
