# Competitive-programming
Algoritmos e ideias de Programação Competitiva

Créditos para: [Tiagosf00](https://github.com/Tiagosf00), [Cebolinha](https://quirino.net/).

## Linux Alias

```bash
alias comp='g++ -std=c++17 -g3 -ggdb3 -O3 -Wall -Wextra  -fsanitize=address,undefined -Wshadow -Wconversion -D_GLIBCXX_ASSERTIONS -o test'
```

*-Wall -Wextra -Wconversion -Wshadow* shows warnings

*-fsanitize=address,undefined* shows errors for memory access error and undefined behaviour (overflow)

*-g3 -ggdb3* shows more details for compilation errors (line that ocurred error)

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

// Utility
#define teto(a, b) ((a+b-1)/(b))
#define LSB(i) ((i) & -(i))
#define MSB(i) (32 - __builtin_clz(i)) // or 64 - clzll
#define BITS(i) __builtin_popcount(i) // count bits

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

## Checklist

**Thinking about solution:**

- Immediately play with the sample cases, you may have understood the problem wrong

- Pay close attention to the constraints

- Always consider doing Binary Search on the answer

- Consider Offline processing

**Before Submitting:**

- Even if the test cases pass, make sure your code is at least doing something

- If the test cases are too simple, come up with a couple extra ones

- Check if constants are big enough

- Check time and memory limits

- Submit the right file

**General:**

- #define int long long

- Fast IO & endl

- Be very careful when copy pasting, check you've changed everything that needs changing

- Be wary of special cases, and when you do define one, be very sure you've correctly identified the full extent of their implications
STL

- Don't call .back(), .front(), .top() on empty containers

- Don't change a container as you iterate through it (Even accessing a map may change it)

- Always make sure your iterators are valid

**Graphs:**

- Add edges both ways if the graph is bidirectional