## Modular Arithmetic

### Basic operations with redundant MOD operators

```cpp
struct OpMOD{
    vector<long long> fact, ifact;

    OpMOD () {}

    OpMOD(long long n){ // from fact[0] to fact[n]; O(n)
        fact.assign(n+1 , 1);
        for(long long i=2; i<=n; i++) fact[i] = mul(fact[i-1], i);

        ifact.assign(n+1, 1);
        ifact[n] = inv(fact[n]);
        for(long long i=n-1; i>=0; i--) ifact[i] = mul(ifact[i+1], i+1);
    }

    long long add(long long a, long long b){
        return ( (a%MOD) + (b%MOD) ) % MOD;
    }

    long long sub(long long a, long long b){
        long long tmp = (a%MOD) - (b%MOD) % MOD;
        if (tmp < 0) tmp += MOD;
        return tmp;
    }

    long long mul(long long a, long long b){
        return ( (a%MOD) * (b%MOD) ) % MOD;
    }

    long long fast_exp(long long n, long long i){ // n ** i
        if (i == 0) return 1;
        if (i == 1) return n;
        long long tmp = fast_exp(n, i/2);
        if (i % 2 == 0) return mul(tmp, tmp);
        else return mul( mul(tmp, tmp), n );
    }

    long long inv(long long n){
        return fast_exp(n, MOD-2);
    }

    long long div(long long a, long long b){
        return mul(a, inv(b));
    }

    long long combination(long long n, long long k){ // n! / (n! (n-k)! )
        return mul( mul(fact[n], ifact[k]) , ifact[n-k]); 
    }

    long long disposition(long long n, long long k){ // n! / (n-k)!
        return mul(fact[n], ifact[n-k]);
    }
};

OpMOD op;
```
