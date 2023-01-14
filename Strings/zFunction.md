## Z-function

Suppose we are given a string  *s*  of length  *n* . The Z-function for this string is an array of length  *n*  where the  *i* -th element is equal to the greatest number of characters starting from the position  *i*  that coincide with the first characters of  *s* .

The first element of the Z-function,  *z[0]* , is generally not well defined. This implementation assumes it as *z[0] = 0*. But it can also be interpreted as *z[0] = n* (all characters coincide).

```cpp
vll z_function(string s) { // O(n)
    ll n = (ll) s.length();
    vll z(n);
    for (ll i=1, l=0, r=0; i<n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;

        if (r < i + z[i] - 1) l = i, r = i + z[i] - 1;
    }
    return z;
}
```

#### Solves

- Find occurrences of pattern string (*pattern*) in the main string (*str*):

```cpp
int32_t main() { sws;
    string str, pattern; cin >> str >> pattern;
    string s = pattern + '$' + str;
    vll z = z_function(s);
    ll ans = 0;
    ll n = pattern.size();
    for(ll i=0; i< (ll) str.size(); i++){
        if( z[i + n + 1] == n)
            ans += 1;
    }
    cout << ans << endl;
}
```

- Find all border lengths of a given string.

**OBS:** A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of *abcababcab* are *ab* and *abcab*.

Works because *z[i] == j* is the condition when the common characters of z[i] reaches the end of the string. For example:

*<ins>ab</ins>cababc<ins>ab</ins>*

z[8] = 2

**ab** is the border;

```cpp
int32_t main(){ sws;
    string s; cin >> s;
    vll z = z_function(s);
    ll n = s.length();
    for(ll i=n-1, j=1; i>=0; i--) {
        if (z[i] == j) cout << j << ' ';
        j += 1;
    }
    cout << endl;
}
```

- Find all period lengths of a string.

**OBS:** A period of a string is a prefix that can be used to generate the whole string by repeating the prefix. The last repetition may be partial. For example, the periods of *abcabca* are *abc*, *abcabc* and *abcabca*.

Works because *z[i] + i >= n* is the condition when the common characters of z[i] in addition to the elements already passed, exceeds or is equal to the end of the string. For example:

*abaababa<ins>ab</ins>*

z[8] = 2

**abaababa** is the period; the remaining (z[i] characters) are a prefix of the period; and when all these characters are combined, it can form the string (which has *n* characters).

```cpp
int32_t main(){ sws;
    string s; cin >> s;
    vll z = z_function(s);
    ll n = s.length();
    for(ll i=1; i<n; i++) {
        if (z[i] + i >= n) {
            cout << i << ' ';
        }
    }
    cout << n << endl;
}
```