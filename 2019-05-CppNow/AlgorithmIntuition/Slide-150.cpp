template <class I, class T, class R, class M> 
auto adjacent_reduce(I f, I l, T init, R r, M m) { 
   return inner_product(f, --l, ++f, init, r, m); 
} 
