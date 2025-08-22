#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int CAT = 0;
int DOG = 1;

int main() {
    int n;
    int total_happiness = 0;
    int cat;
    int dog;
    int difference;
    cin >> n;
    int cats_left = n;
    int dogs_left = n;

    // Cats, Dogs, Difference
    vector<vector<int>> preferences(2*n);

    for (int i = 0; i < 2*n; i ++) {
        cin >> cat;
        cin >> dog;
        difference = abs(cat - dog);

        preferences[i] = {cat, dog, difference};
    }

    sort(preferences.begin(), preferences.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] > b[2];
    });

    for (int j = 0; j < 2*n; j++) {
        if ((preferences[j][CAT] >= preferences[j][DOG] && cats_left > 0) || dogs_left == 0) {
            cats_left -= 1;
            total_happiness += preferences[j][CAT];
            continue;
        } 

        if ((preferences[j][DOG] >= preferences[j][CAT] && dogs_left > 0) || cats_left == 0) {
            dogs_left -= 1;
            total_happiness += preferences[j][DOG];
            continue;
        }
    }

    cout << total_happiness;
}