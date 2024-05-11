/**
 * Author: Wallace, cp-algorithms
 * Date: 14/02/2024
 * Description: Linear Sieve that iterates every value
 * once (prime) or twice (composite)
 * Time: O(N)
 * Status: Tested (https://codeforces.com/contest/776/submission/246424361)
 */

vector<ll> primes, lp(MAX);
// lp[i] = smallest prime divisor of i

void linearSieve(ll n) {
    for (ll i=2; i <= n; i++) {
        if (lp[i] == 0) { // i is prime
            lp[i] = i; // {lp[i] == i} for prime numbers
            primes.pb(i);
        }
        // visit every composite number that has primes[j] as the lp
        for (ll j = 0; i * primes[j] <= n; j++) {
            lp[i * primes[j]] = primes[j];
            
            if (primes[j] == lp[i])
                break;
        }
    }
}