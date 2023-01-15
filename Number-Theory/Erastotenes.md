## Crivo de Eratóstenes

```cpp
vector<int> crivo(int n){
    int max = 1e6;
    vector<int> primes {2};
    bitset<max> sieve;
    sieve.set();

    for(int i=3; i<=n; i+=2){
        if(sieve[i]){ // i is prime
            primes.push_back(i);

            for(int j= i*i; j<=n; j += 2*i) // sieving all odd multiples of i >= i*i
                sieve[j] = false;
        }
    }

    return primes;
}
```

#### Optimized

```cpp
// O (N log^2(N) ) -> Teorema de Merten

vll primes {2, 3};
set<ll> isPrime = {2, 3};
void eratostenes(ll n){ 
    bitset<MAX> sieve;
    sieve.set();
    for(ll i=5, step=2; i<=n; i+=step, step = 6 - step){
        if(sieve[i]){ // i is prime
            primes.push_back(i);
            isPrime.insert(i);
            for(ll j= i*i; j<=n; j += 2*i) // sieving all odd multiples of i >= i*i
                sieve[j] = false;
        }
    }
}
```

### Linear Sieve

Computes all primes and composites between [2, n] in O(n) time.

Note that every composite *q* must have at least one prime factor, so we can pick the smallest prime factor *p*, and let the rest of the part be i, i.e. *q = ip*.

Since *p* is the smallest prime factor, we have *i ≥ p* (this garantees that *p* will already exist in the vector when reached by *i*)

Also, no prime less than *p* can divide *i* (break point).

Now let us take a look at the code we have a moment ago. This way, it's possible to pick out each composite exactly once.

```cpp
vector<int> prime;
bool is_composite[MAX]; // can be 1e7

void sieve (int n) { // O(n)
	fill(is_composite, is_composite + n, false);

	for (int i = 2; i <= n; i++) {
		if (!is_composite[i]) prime.pb(i);
		for (int j = 0; j < (int) prime.size () && i * prime[j] <= n; j++) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}
```