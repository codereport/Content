adjacent_inclusive_scan(cbegin(v), 
                        cend(v), 
                        begin(u), 
                        std::plus(), 
                        [](auto a, auto b) { 
                           return a == b ? b : 0; 
                        }); 
