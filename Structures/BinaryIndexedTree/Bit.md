## BIT ( Fenwick Tree or Binary indexed tree)

*OBS:* BIT cannot support min/max queries, because it's mandatory to have an inverse operation.

Let's define **g(i)** as the number acquired after removing the **LSB(i)** of **i**:

    g(i) = i - LSB(i) = i - (i & (-i))

Then, each value of the **Bit vector** will be resposible to store the range value of:

    (g(i), i]

Therefore, to retrieve the range value of an arbitrary value **x**, it's only necessary to merge:

    Bit[i] + Bit[g(i)] + Bit[g(g(i))] + ...

In the 1-Indexed implementation, Bit[0] is undefined and not used.

**Complexity** O(log(n)): add, sum, query

### 1-indexed Implementation

```cpp
struct FT {
    vll bit;
    ll n;

    // constructor (all zeros)
    FT(ll sz) : n(sz) { 
        bit.assign(sz + 1, 0);
    }

    void add(ll idx, ll delta) { // add delta to current value
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    // sum from 1 to idx [inclusive]
    // idx is also 1-idx, obviously
    ll sum(ll idx) { 
        ll ans = 0;
        for (; idx >= 1; idx -= idx & -idx) // LSB
            ans += bit[idx];
        return ans;
    }

    ll query(ll l, ll r) { // sum of [l, r]
        return sum(r) - sum(l - 1);
    }
};
```