/**
 * Author: Wallace, Quirino
 * Date: 31/03/2024
 * Description: Good randomizer to generate int in a range or shuffle vectors
 * Time: O(1) for randint, O(n log(n)) for shuffle
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// or for 64 bits
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// to shuffle a vector
vector<int> vec;
shuffle(vec.begin(), vec.end(), rng);

// to limit the number to the range [l, r]
int randint(int l, int r) {
    return (rng() % (r-l+1)) + l;
}