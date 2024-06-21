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
#define MSB(i) (63 - __builtin_clzll(i))
#define BITS(i) __builtin_popcountll(i)

template<class A, class B> auto& operator<<(ostream &os, pair<A, B> p) { 
    return os << '{' << p.ff << ", " << p.ss << '}'; }
template<class... A>void db(A ...a) {((cerr<<"{"<<a<<"} "), ...); cerr<<endl;}
template<class A>void db2(A a) {for(auto b:a) {cerr<<b<<" ";} cerr<<endl;}
template<class A>void db3(A a) {for(auto b:a) db2(b);}
#define dbg(...) {cerr << #__VA_ARGS__ << ": "; db(__VA_ARGS__); }
#define deb(a) {cerr << #a << ": "; db2(a); }
#define debug(a) {cerr << #a << ": " << endl; db3(a); }

const ll MAX = 2e5+10;
const ll MOD = 998'244'353;
const ll INF = 1e18; // INT32_MAX
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
