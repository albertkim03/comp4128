#include <bitset>
using BS = std::bitset<200000>;      // size must be a compile-time constant

BS b;                                 // all zeros
b.set(i);                             // set bit i to 1
b.reset(i);                           // set bit i to 0
b.flip(i);                            // toggle bit i
b[i] = 1;                             // index access (returns proxy)
bool x = b.test(i);                   // read bit i (bounds-checked)
size_t k = b.count();                 // number of 1s (popcount)
bool ok = b.any();                    // any bit is 1?
bool z  = b.none();                   // all zero?
bool z  = b.all();                   // all one?
b.reset();                            // clear all
b.set();                              // set all to 1 (careful)
auto s = b.to_string();               // MSB..LSB string
// Bitwise ops (produce new bitsets of same size):
BS a, c;
BS d = a & c;
d |= (a << 5);                        // left shift by 5, vacated bits become 0
