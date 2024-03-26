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
#define MSB(i) (63 - __builtin_clzll(i)) // for ll
#define BITS(i) __builtin_popcountll(i)

template<class A> void debug(A a) {
    cout << "container: ";
    for(auto b : a) cout << b << " ";
    cout << endl;
}
template<class... A> void dbg(A const&... a) {
    ((cout << "{" << a << "} "), ...);
    cout << endl;
}

const ll MAX = 2e5+10;
const ll MOD = 1e9 + 7;
const ll INF = INT32_MAX; // INT64_MAX
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