/**
 * Author: Wallace
 * Date: 06/11/2024
 * Description: Getline code example and stringstream object
 * Time: O(1)
*/

// By default, cin does NOT consume the last whitespace character,
// including a newline character, which will be left on the input stream
// So if using cin before a getline, the ws should be explicitly read

// Also by default, getline DOES consume the last whitespace character
// but this whitespace won't be stored in the string

int32_t main() {

    // ws is input manipulator to retrieve the whitespace character
    ll n; cin >> n >> ws; 
    string line;
    
    // the second line is therefore stored in the object "line". 
    getline(cin, line); 

    stringstream ss(line);
    string word;
    while(ss >> word) {
        // word split by white spaces {like python's .split()}
    }
}