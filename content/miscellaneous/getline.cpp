/**
 * Author: Wallace
 * Date: 04/05/2024
 * Description: Getline code example
 * Time: O(1)
*/

int32_t main() {
    // ws is input manipulator to retrieve the whitespace character
    ll n; cin >> n >> ws; 
    string line;
    // the second line is therefore stored in the object "line". The default delimiter \n is not stored. 
    getline(cin, line); 
}