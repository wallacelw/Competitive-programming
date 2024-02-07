/**
 * Author: Wallace, CP-Algorithms
 * Date: 07/02/2024
 * Description: Computes the prefix function
 * Time: O(n)
 * Status: Tested (https://cses.fi/problemset/result/8412101/)
 */

vector<ll> kmp(string &s) { // O(n)
    ll n = (ll) s.length();
    vector<ll> pi(n);
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}