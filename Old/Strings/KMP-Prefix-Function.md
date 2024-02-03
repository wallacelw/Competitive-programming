## KMP algorithm for computing the prefix function

pi[i] = longest proper (not equal to the whole string) prefix of the substring s[0:i] which is also suffix of this substring.

```cpp
vector<int> prefix_function(string s) { // O(n)
    int n = (int) s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
```
