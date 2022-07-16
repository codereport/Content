
// https://codeforces.com/contest/1272/submission/66690239

auto solve(string s) -> string {
    auto u  = count(s.begin(), s.end(), 'U');
    auto d  = count(s.begin(), s.end(), 'D');
    auto l  = count(s.begin(), s.end(), 'L');
    auto r  = count(s.begin(), s.end(), 'R');
    auto ud = min(u, d);
    auto lr = min(l, r);
    if (lr == 0 && ud == 0) return "";
    if (ud == 0) return "LR";
    if (lr == 0) return "UD";
    string ans(ud,          'U');
    ans.resize(ud + lr,     'L');
    ans.resize(ud*2 + lr,   'D');
    ans.resize(ud*2 + lr*2, 'R');
    return ans;
}
