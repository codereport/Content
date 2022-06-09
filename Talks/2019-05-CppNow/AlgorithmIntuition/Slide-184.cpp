auto calc_word_score(vector<int> const& word, 
                     vector<int> const& tile) -> int { 
    return transform_reduce(cbegin(word), 
                            cend(word), 
                            cbegin(tile), 
                            0);                           
} 
