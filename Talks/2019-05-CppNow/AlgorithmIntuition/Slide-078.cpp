namespace my { 
   template<class I, class T> 
   auto count(I f, I l, T const& val) -> int { 
      return std::transform_reduce(f, l, 0, 
         [](auto a, auto b) { return a + b; },
         [val](auto x) { return static_cast<int>(x == val); }
      ); 
   } 
} 
