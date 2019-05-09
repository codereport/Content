namespace my { 
   template<class I, class P> 
   auto any_of(I f, I l, P p) -> bool { 
      return std::reduce(f, l, false, 
         [p](auto a, auto b) { return a || p(b); }); 
   } 
} 
