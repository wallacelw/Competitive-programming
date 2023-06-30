### Operations with Combinatorics

Also contains combinatorics operations

```cpp
struct OpMOD{
    vll fact, ifact;

    OpMOD () {}

    // overloaded constructor that computes factorials
    OpMOD(ll n){ // from fact[0] to fact[n]; O(n)
        fact.assign(n+1 , 1);
        for(ll i=2; i<=n; i++) fact[i] = mul(fact[i-1], i);

        ifact.assign(n+1, 1);
        ifact[n] = inv(fact[n]);
        for(ll i=n-1; i>=0; i--) ifact[i] = mul(ifact[i+1], i+1);
    }

    ll add(ll a, ll b){
        return ( (a%MOD) + (b%MOD) ) % MOD;
    }

    ll sub(ll a, ll b){
        return ( ((a%MOD) - (b%MOD)) + MOD ) % MOD;
    }

    ll mul(ll a, ll b){
        return ( (a%MOD) * (b%MOD) ) % MOD;
    }

    ll fast_exp(ll n, ll i){ // n ** i
        if (i == 0) return 1;
        if (i == 1) return n;
        ll tmp = fast_exp(n, i/2);
        if (i % 2 == 0) return mul(tmp, tmp);
        else return mul( mul(tmp, tmp), n );
    }

    ll inv(ll n){
        return fast_exp(n, MOD-2);
    }

    ll div(ll a, ll b){
        return mul(a, inv(b));
    }

    // n! / (n! (n-k)! )
    ll combination(ll n, ll k){ // "Combinação/Binomio de Newton"
        if(k > n) return 0;
        return mul( mul(fact[n], ifact[k]) , ifact[n-k]); 
    }

    // n! / (n-k)!
    ll disposition(ll n, ll k){ // "Arranjo Simples"
        if(k > n) return 0;
        return mul(fact[n], ifact[n-k]);
    }

    // n! 
    ll permutation(ll n){ // "Permutação Simples"
        return fact[n];
    }

    // n! / (k1! k2! k3!)
    ll permutationRepetition(ll n, vll x) { // "Permutação com Repetição" 
        ll tmp = fact[n];
        for(auto k : x) tmp = mul(tmp, ifact[k]);
        return tmp;
    }

    // (n+m-1)! / ((n-1)! (m!)) 
    ll starBars(ll n, ll m) { // "pontos e virgulas"
        // n Groups -> n-1 Bars
        // m Stars
        return combination(n+m-1, m);
    }

    // !n = (n-1) * ( !(n-1) + !(n-2) )
    vll subfactorial; // derangements
    void computeSubfactorials(ll n) {
        subfactorial.assign(n+1, 0);
        subfactorial[0] = 1;
        // !0 = 1
        // !1 = 0
        for(ll i=2; i<=n; i++) {
            subfactorial[i] = mul( (i-1) , add(subfactorial[i-1], subfactorial[i-2]) );
        }
    }
};

// remember to pass a number delimeter (n) to precompute factorials 
OpMOD op;
```

### Overloading Operations Struct

```cpp
const int MOD = 1e9+7;

struct intM{
    long long val = 0;

    intM(long long n=0){
        val = n%MOD;
        if (val < 0) val += MOD;
    }
    
    bool operator ==(const intM& b) const{
        return (val == b.val);
    }

    intM operator +(const intM& b) const{
        return (val + b.val) % MOD;
    }

    intM operator -(const intM& b) const{
        return (val - b.val + MOD) % MOD;
    }

    intM operator *(const intM& b) const{
        return (val*b.val) % MOD;
    }

    intM operator ^(const intM& b) const{ // fast exp [(val^b) mod M];
        if (b == 0) return 1;
        if (b == 1) return (*this);
        intM tmp = (*this)^(b.val/2); // diria que não vale a pena definir "/", "/" já é a multiplicação pelo inv
        if (b.val % 2 == 0) return tmp*tmp; // diria que não vale a pena definir "%", para não confidir com o %MOD
        else return tmp * tmp * (*this);
    }

    intM operator /(const intM& b) const{ 
        return (*this) * (b ^ (MOD-2));
    }
};
```