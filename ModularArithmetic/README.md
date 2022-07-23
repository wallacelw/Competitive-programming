
// * Modular Arithmetic

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