/**
 * Author: Wallace, CP-Algorithms
 * Date: 07/02/2024
 * Description: Covert String to odd length to use manacher, which
 * computes all the maximum lengths of all palindromes in the given string
 * Time: O(2n)
 * Status: Tested (https://cses.fi/problemset/result/8411794/)
 */

struct Manacher {
    string s, t;
    vector<ll> cnt;

    // t is the transformed string of s, with odd size
    Manacher(string &s_) : s(s_) {
        t = "#";
        for(auto c : s) {
            t += c, t += "#";
        }
        count();    
    }

    // perform manacher on the odd string
    // cnt will give all the palindromes centered in i
    // for the odd string t
    void count() { 
        ll n = t.size();
        string aux = "$" + t + "^";
        vector<ll> p(n + 2);
        ll l = 1, r = 1;
        for(ll i = 1; i <= n; i++) {
            p[i] = max(0LL, min(r - i, p[l + (r - i)]));
            while(aux[i - p[i]] == aux[i + p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        cnt = vector<ll>(p.begin() + 1, p.end() - 1);
    }

    // compute a longest palindrome present in s
    string getLongest() {
        ll len = 0, pos = 0;
        for(ll i=0; i<(ll)t.size(); i++) {
            ll sz = cnt[i]-1;
            if (sz > len) {
                len = sz;
                pos = i;
            }
        }
        return s.substr(pos/2 - len/2, len);
    }
};
