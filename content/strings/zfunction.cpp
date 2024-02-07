/**
 * Author: Wallace, CP-Algorithms
 * Date: 07/02/2024
 * Description: For each substring starting at position i,
 * compute the maximum match with the original prefix. z[0] = 0
 * Time: O(n)
 */

vector<ll> z_function(string &s) { // O(n)
    ll n = (ll) s.length();
    vector<ll> z(n);
    for (ll i=1, l=0, r=0; i<n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);

        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;

        if (r < i + z[i] - 1) l = i, r = i + z[i] - 1;
    }
    return z;
}