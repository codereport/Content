int solve(int h, vector<int> w, vector<int> l) {
   return max(0, inner_product(begin(w), begin(l), 0, 
      [](auto a, auto b) { return max(a, b); }, 
      [](auto a, auto b) { a - b / 4; });
}
