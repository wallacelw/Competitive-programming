# Competitive-programming
Algoritmos e ideias de programação competitiva

Créditos para: [Tiagosf00](https://github.com/Tiagosf00).

## Flags for compilation:

```bash
g++ -Wall -Wextra -Wshadow -ggdb3 -D_GLIBCXX_ASSERTIONS -fmax-errors=2 -std=c++17 -O3 test.cpp -o test
```

## Linux Alias

```bash
alias comp='g++ -std=c++17 -g -O2 -Wall -Wextra -Wconversion -Wshadow -D_GLIBCXX_ASSERTIONS -fsanitize=address,undefined -fno-sanitize-recover -ggdb -o out'
```

## Template:

```cpp
// Needed
#include <bits/stdc++.h>
using namespace std;
#define sws cin.tie(0)->sync_with_stdio(0)

// Life Quality
#define endl '\n'
#define ll long long
#define vll vector<ll>
#define pb push_back
#define ld long double
#define vld vector<ld>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define ff first
#define ss second
#define tlll tuple<ll, ll, ll>

// Extra
#define teto(a, b) ((a+b-1)/(b))
#define LSB(i) ((i) & -(i))
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Debugging
#define db(a) cerr << " [ " << #a << " = " << a << " ] " << endl;
#define debug(a...) cerr<<#a<<": ";for(auto &b:a)cerr<<b<<" ";cerr<<endl;
template <typename... A> void dbg(A const&... a) { ((cerr << "{" << a << "} "), ...); cerr << endl; }

// Constants
const int MAX = 2e5+10;
const long long MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const long long LLINF = 0x3f3f3f3f3f3f3f3f;
const long double EPS = 1e-7;
const long double PI = acos(-1);

int32_t main(){ sws;

}
```
