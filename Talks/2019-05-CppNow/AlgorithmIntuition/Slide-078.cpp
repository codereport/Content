namespace my { 
   template<class I, class T> 
   auto count(I f, I l, T const& val) -> int { 
      return std::reduce(f, l, 0, 
         [val](auto a, auto b) { return a + (b == val); }); 
   } 
} 
