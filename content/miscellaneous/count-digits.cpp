/**
 * Author: Wallace
 * Date: 02/08/2024
 * Description: count the number of digits d used in range [1, n]
 * Time: O(18)
 * Status: Tested (https://cses.fi/problemset/result/10057923/)
*/

// count the number of digits d used in range [1, n]
ll count_digits(ll n, ll d) {
    ll cnt = 0, t = 1;
    for(ll i=0; i<18; i++, t *= 10) {
        ll sz = n + 1 - t * ( (d == 0) ? 10 : d );
        if (sz <= 0) break;
        ll intervals = sz / (t * 10);
        ll use = intervals * t;
        ll last = sz - intervals * t * 10;
        cnt += use + max(0LL, min(last, t));
    }
    return cnt;
}