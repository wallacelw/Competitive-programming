### Getline

```cpp
int32_t main() {
    ll n; cin >> n >> ws; // ws is input manipulator to retrieve the whitespace character
    string line;
    getline(cin, line); // the second line is therefore stored in the object "line". The default delimiter \n is not stored. 
}
```

**NOTE:** When consuming whitespace-delimited input (e.g. int n; std::cin >> n;) any whitespace that follows, including a newline character, will be left on the input stream. Then when switching to line-oriented input, the first line retrieved with getline will be just that whitespace. In the likely case that this is unwanted behaviour.