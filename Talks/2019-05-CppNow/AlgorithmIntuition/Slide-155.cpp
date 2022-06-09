auto dangerous_team(const string& s) -> bool { 
   auto max_players = 1, curr_players = 1; 
   for (int i = 1; i < s.size(); ++i) { 
      curr_players = s[i] == s[i - 1] ? ++curr_players : 1; 
      max_players = max(max_players, temp); 
   } 
   return max_players >= 7; 
} 
