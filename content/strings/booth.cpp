/**
 * Author: Wallace
 * Date: 07/02/2024
 * Description: Use a modified version of KMP to find the
 * lexicographically minimal string rotation
 * Time: O(n)
 * Status: Tested (https://cses.fi/problemset/result/8412049/)
 */

// Booth Algorithm
ll least_rotation(string &s) { // O(n)
    ll n = s.length();
    vector<ll> f(2*n, -1);
    ll k = 0;
    for(ll j=1; j<2*n; j++) {
        ll i = f[j-k-1];
        while(i != -1 and s[j % n] != s[(k+i+1) % n] ) {
            if (s[j % n] < s[(k+i+1) % n])
                k = j - i - 1;
            i = f[i];
        }
        if (i == -1 and s[j % n] != s[(k+i+1) % n] ) {
            if (s[j % n] < s[(k+i+1) % n])
                k = j;
            f[j - k] = -1;
        }
        else
            f[j - k] = i + 1;
    }
    return k;
}

int32_t main(){ sws;
    string s; cin >> s;
    ll n = s.length();
    ll ans_idx = least_rotation(s);
    string tmp = s + s;
    cout << tmp.substr(ans_idx, n) << endl;
}