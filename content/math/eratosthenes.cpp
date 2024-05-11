/**
 * Author: Wallace, Edson
 * Date: 14/02/2024
 * Description: Optimized sieve of eratosthenes
 * Time: O(N \log{\log{N}})
 */

// O (N log^2(N) ) -> Teorema de Merten
vector<ll> primes {2, 3};
bitset<MAX> sieve; // {sieve[i] == 1} if i is prime
// MAX can be ~1e7

void eratostenes(ll n){ 
    sieve.set();
    for(ll i=5, step=2; i<=n; i+=step, step = 6 - step){
        if(sieve[i]){ // i is prime
            primes.pb(i);
            for(ll j= i*i; j<=n; j += 2*i) // sieving all odd multiples of i >= i*i
                sieve[j] = false;
        }
    }
}