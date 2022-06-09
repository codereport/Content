auto dangerous_team(string const& s) -> bool { 
   return adjacent_reduce(cbegin(s), cend(s), 
      make_pair(1, 1), 
      [](pair<int, int> acc, bool equal) { 
         auto [max_player, curr_player] = acc; 
         curr_player = equal ? ++curr_player : 1; 
         return make_pair(max(max_player, curr_player), curr_player); 
      }, 
      std::equal_to{}).first >= 7; 
} 
