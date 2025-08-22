#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    long long iron;
    long long gold;
    long long diamond;

    cin >> iron >> gold >> diamond;

    if (diamond % 2 == 0) {
        // Steve's turn
        if (iron > gold) {
            cout << "Steve";
        } else {
            cout << "Alex";
        }
    } else {
        // Alex turn
        if (gold > iron) {
            cout << "Alex";
        } else {
            cout << "Steve";
        }
    }

    return 0;
}
