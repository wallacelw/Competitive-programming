## Disjoint Set Union

```cpp
struct DSU{
    vll group;
    vll card;
    DSU (long long n){
        group = vll(n);
        iota(group.begin(), group.end(), 0);
        card = vll(n, 1);
    }
    long long find(long long i){
        return (i == group[i]) ? i : (group[i] = find(group[i]));
    }
    void join(long long a ,long long b){
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (card[a] < card[b]) swap(a, b);
        card[a] += card[b];
        group[b] = a;
    }
};
```

#### Avisos

Possui a optimização de **Compressão** e **Balanceamento**

Both are: *O(a(N)) ~ O(1)*:

**find(i)**: finds the representative of an element and returns it

**join(a, b)**: finds both representatives and unites them, remaining only one for all. No return value