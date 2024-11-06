// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
#define sws cin.tie(0)->sync_with_stdio(0)

typedef long long ll;
typedef long double ld;
#define endl '\n'
#define pb push_back
#define ff first
#define ss second
#define pll pair<ll, ll>
#define vll vector<ll>

#define teto(a, b) (((a)+(b)-1)/(b))
#define LSB(i) ((i) & -(i))
#define MSB(i) (64 - 1 - __builtin_clzll(i))
#define BITS(i) __builtin_popcountll(i)

template<class...A> void dbg(A...a) {
    ((cerr << "{" << a << "} "), ...); 
    cerr << endl;
}
template<class A> void deb(A a) {
    for(auto b : a) cerr << b << " ";
    cerr << endl;
}
template<class A> void debug(A a) {
    for(auto b : a) deb(b);
}

const ll MAX = 1e6+10;
const ll MOD = 998'244'353;
const ll INF = 0x3f3f3f3f3f3f3f3f; // INT64_MAX
const ld EPS = 1e-7;
const ld PI = acos(-1);

#include <chrono>
using namespace std::chrono;
int32_t main(){ sws;
    auto start = high_resolution_clock::now();
    // function to be timed here
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;
}
