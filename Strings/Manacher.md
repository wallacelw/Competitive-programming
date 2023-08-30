## Manacher's Algorithm 

For each substring, centered at i, find the longest palindrome that can be formed. The value stored in manacher(s) is palindrome_len + 1. 

```cpp
// returns the size of the maximum palidrome centered in i
vector<int> manacher_odd(string s) { // O(n)
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

// changing all even palindromes to odd ones
string t = "#";
vector<int> manacher(string s) {
    for(auto c: s) t += c + string("#");
    return manacher_odd(t);
}

// main functions to print the biggest subpalindrome
int32_t main() { sws;
    string s; cin >> s;
    auto len = manacher(s);

    ll ans = 0, pos = 0;
    for(ll i=0; i<t.size(); i++) {
        ll sz = len[i]-1;
        if (sz > ans) {
            ans = sz;
            pos = i;
        }
    }
    
    cout << s.substr(pos/2 - ans/2, ans) << endl;
}
```
