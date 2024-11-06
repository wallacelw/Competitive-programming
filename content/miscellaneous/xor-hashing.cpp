/**
 * Author: Quirino
 * Date: 06/11/2024
 * Description: Hashing of a set of elements using xor
 * Time: O(elements)
 * Status: just copied
 */

// XOR Hash {{{
unsigned long long mix(unsigned long long o){
  o+=0x9e3779b97f4a7c15;
  o=(o^(o>>30))*0xbf58476d1ce4e5b9;
  o=(o^(o>>27))*0x94d049bb133111eb;
  return o^(o>>31);
}
//}}}