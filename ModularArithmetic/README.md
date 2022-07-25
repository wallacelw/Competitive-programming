# Modular Arithmetic

!! NOT REALLY TESTED !!

```cpp

class OpMOD{
    public:
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
};

```

## Faster operations and more complex ones

It assumes that all numbers that are given are already between [0, MOD)

```cpp
class OpMOD{
    public:
        long long add(long long a, long long b){
            return (a+b >= MOD) ? (a+b-MOD) : (a+b);
        }
        long long sub(long long a, long long b){
            return (a-b < 0) ? (a-b+MOD) : (a-b);
        }
        long long mul(long long a, long long b){
            return (a*b) % MOD;
        }
        long long fast_exp(long long n, long long i){ // n ** i;  O(log(i))
            long long ans = 1;
            while(i > 0){
                if (i & 1) ans = mul(ans, n);
                n = mul(n, n);
                i >>= 1; // i = floor(i / 2)
            }
            return ans;
        }
        long long inv(long long n){
            return fast_exp(n, MOD-2);
        }
        long long div(long long a, long long b){
            return mul(a, inv(b));
        }

        vector<long long> fact;

        void buildFact(long long n){ // from fact[0] to fact[n]; O(n)
            fact = vector<long long>(n+1);
            fact[0] = fact[1] = 1;
            for(long long i=2; i<=n; i++) fact[i] = mul(fact[i-1], i);
        }

        vector<long long> ifact;

        void buildIfact(long long n){ // from ifact[0] to ifact[n], requires FACT; O(n)
            ifact = vector<long long>(n+1);
            ifact[n] = inv(fact[n]);
            for(long long i=n-1; i>=0; i--) ifact[i] = mul(ifact[i+1], i+1);
        }
};
```