auto dangerous_team(string const& s) -> bool { 
   return adjacent_reduce(cbegin(s), cend(s), 
      make_pair(1, 1), 
      [](pair<int, int> acc, bool equal) { 
         auto [mp, cp] = acc; 
         cp = equal ? ++cp : 1; 
         return make_pair(max(mp, cp), cp); 
      }, 
      std::equal_to{}).first >= 7; 
} 
