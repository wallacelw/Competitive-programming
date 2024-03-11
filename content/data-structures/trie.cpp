/**
 * Author: Wallace, Tiago
 * Date: 11/03/2024
 * Description: Creates a trie by pre-allocating the trie array, which contains the indices for the child nodes.
 * The trie can be easily modified to support alphanumeric strings instead of binary strings.
 * Time: O(D), D = depth of trie
 * Status: Tested (https://cses.fi/problemset/result/5250973/)
 */

// MAX = maximum number of nodes that can be created

struct Trie{
    ll trie[MAX][26];
    bool isWordEnd[MAX];
    ll nxt = 1, wordsCnt = 0;
 
    void add(string s){ // O(Depth)
        ll node = 0;
        for(auto c: s) {
            if(trie[node][c-'a'] == 0) { // create new node
                trie[node][c-'a'] = nxt++;
            }
            node = trie[node][c-'a'];
        }
        if(!isWordEnd[node]){
            isWordEnd[node] = true;
            wordsCnt++;
        }
    }
 
    bool find(string s, bool remove=false){ // O(Depth)
        ll node = 0;
        for(auto c: s) {
            if(trie[node][c-'a'] == 0) {
                return false;
            }
            else {
                node = trie[node][c-'a'];
            }
        }
 
        if(remove and isWordEnd[node]){
            isWordEnd[node] = false;
            wordsCnt--;
        }

        return isWordEnd[node];
    }
};