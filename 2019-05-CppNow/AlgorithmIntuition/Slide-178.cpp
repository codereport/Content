template<class I, class O, class BinOp1, class BinOp2> 
auto adjacent_inclusive_scan(I f, I l, O o, BinOp1 binop1, 
                                            BinOp2 binop2) { 
   if (f != l) { 
      auto prev = *f; // previous element 
      auto acc  = *f; // accumulator 
      *o = prev;      // first element special treatment 
      while (++f != l) { 
         acc = binop1(acc, binop2(*f, prev)); 
         *++o = acc; 
         prev = std::move(*f); 
      } 
      ++o; 
   } 
   return o; 
} 
