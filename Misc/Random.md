
## Random Numbers Generator

**HOW TO USE :**

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// to shuffle a vector
vector<int> vec;
shuffle(vec.begin(), vec.end(), rng);

// to simply generate a unsigned 32 bit number
unsigned int num = rng();

// to limit the number to the range [0, n[
unsigned int num = rng() % n;

// to limit the number to the range [1, n]
unsigned int num = rng() % n + 1;
```

*For 64-bit numbers:* mt19937_64