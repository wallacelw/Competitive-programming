/**
 * Author: Wallace, Tiago
 * Date: 08/07/2024
 * Description: Creates a trie by pre-allocating the trie array, which contains the indices for the child nodes.
 * The trie can be easily modified to support alphanumeric strings instead of binary strings.
 * Time: O(D), D = depth of trie
 * Status: Tested (https://cses.fi/problemset/result/9792405/)
 */

ll alphabet = 26;

struct Trie {
    vector<vll> t;
    vector<ll> words;
    ll idx = 1;
    
    // n = maximum number of nodes to be created = N*len
    Trie(ll n) : t(n, vll(alphabet, 0)), words(n, 0) {}

    void add(string s){ // O(Depth)
        ll node = 0;
        for(auto c : s) {
            if(t[node][c-'a'] == 0) { // create new node
                t[node][c-'a'] = idx++;
            }
            node = t[node][c-'a'];
        }
        words[node]++;
    }
};