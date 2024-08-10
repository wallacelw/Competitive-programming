/**
 * Author: Wallace, cp-algorithms
 * Date: 14/02/2024
 * Description: Linear Sieve that iterates every value
 * once (prime) or twice (composite)
 * Time: O(N)
 * Status: Tested (https://codeforces.com/contest/776/submission/246424361)
 */

vector<ll> primes, sp(MAX); // MAX = ~1e7
// sp[i] = smallest prime divisor of i
// after running sieve(), sp[i] == i for primes

void sieve(ll n) {
    for (ll i=2; i <= n; i++) {
        if (sp[i] == 0) { // i is prime
            sp[i] = i; // {sp[i] == i} for prime numbers
            primes.pb(i);
        }
        // visit every composite number that has primes[j] as the sp
        for (ll j = 0; i * primes[j] <= n; j++) {
            sp[i * primes[j]] = primes[j];
            if (primes[j] == sp[i]) break;
        }
    }
}