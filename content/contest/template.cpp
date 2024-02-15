#include <bits/stdc++.h>
using namespace std;
#define sws cin.tie(0)->sync_with_stdio(0)

#define endl '\n'
#define ll long long
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define pll pair<ll, ll>
#define vll vector<ll>

#define teto(a, b) ((a+b-1)/(b))
#define LSB(i) ((i) & -(i))
#define MSB(i) (32 - __builtin_clz(i)) //64 - clzll
#define BITS(i) __builtin_popcountll(i) //count set bits

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define debug(a...) cerr<<#a<<": ";for(auto b:a)cerr<<b<<" ";cerr<<endl;
template<typename... A> void dbg(A const&... a){((cerr<<"{"<<a<<"} "), ...);cerr<<endl;}

const ll MAX = 3e5+10;
const ll MOD = 1e9+7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll LLINF = INT64_MAX;
const ld EPS = 1e-7;
const ld PI = acos(-1);

#include <chrono>
using namespace std::chrono;
int32_t main(){ sws;
    auto start = high_resolution_clock::now();
    // function here
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;
}  