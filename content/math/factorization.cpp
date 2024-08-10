/**
 * Author: Wallace
 * Date: 09/08/2024
 * Description: Factorization
 * Time: O(\sqrt{n}) for trial division; O(\log2(n)) using smallest prime
 * Status: Tested (https://codeforces.com/contest/895/my)
 */

vector<ll> factorization(ll n){ // O(sqrt(n))
    vector<ll> factors;
    for(auto p : prime){
        if (p*p > n) break;
        while(n % p == 0){
            factors.pb(p);
            n /= p;
        }
    }
    if (n > 1) factors.pb(n);
    return factors;
}

// import linear sieve 
vector<ll> factorization(ll a) { // log2(a)
    vector<ll> factors;
    while(a > 1) {
        factors.pb(sp[a]);
        a /= sp[a];
    }
    return factors;
}