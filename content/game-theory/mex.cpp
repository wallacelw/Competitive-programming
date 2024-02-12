/**
 * Author: Wallace
 * Date: 12/02/2024
 * Description: Compute MEX efficiently by keeping track of the frequency
 * of all existent elements and also the missing ones
 * Time: O(\log{N}) per addition/removal, O(1) to get mex value, O(N \log(N)) to initialize
 */

struct MEX {
    map<ll, ll> freq;
    set<ll> missing;

    // initialize set with values up to {max_valid_value} inclusive
    MEX(ll max_valid_value) { // O(n log(n))
        for(ll i=0; i<=max_valid_value; i++)
            missing.insert(i);
    }

    ll get() { // O(1)
        if (missing.empty()) return 0;
        return *missing.begin();
    }

    void remove(ll val) { // O(log(n))
        freq[val]--;
        if (freq[val] == 0)
            missing.insert(val);
    }

    void add(ll val) { // O(log(n))
        freq[val]++;
        if (missing.count(val))
            missing.erase(val);
    }
};