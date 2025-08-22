#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>
using namespace std;

int n, m;

// Returns square number from (row, col)
int get_square_number(int row, int col) {
    int row_from_bottom = n - 1 - row;
    if (row_from_bottom % 2 == 0)
        return row_from_bottom * n + col + 1;
    else
        return row_from_bottom * n + (n - col);
}

// Returns (row, col) from square number (1-based)
pair<int, int> get_coordinates(int square) {
    int row_from_bottom = (square - 1) / n;
    int pos_in_row = (square - 1) % n;
    int actual_row = n - 1 - row_from_bottom;
    int col = (row_from_bottom % 2 == 0) ? pos_in_row : (n - 1 - pos_in_row);
    return {actual_row, col};
}

// Advances position by `steps`, returns new (row, col)
pair<int, int> move_forward(int row, int col, int steps) {
    int square = get_square_number(row, col);
    square = min(n * n, square + steps);
    return get_coordinates(square);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(n));
    unordered_map<char, pair<int, int>> seen;
    unordered_map<int, int> teleport;

    // Read board and prepare teleport map
    for (int row = 0; row < n; row++) {
        string s;
        cin >> s;
        for (int col = 0; col < n; col++) {
            char c = s[col];
            grid[row][col] = c;
            if (isalpha(c)) {
                if (seen.count(c)) {
                    pair<int, int> prev = seen[c];
                    int pr = prev.first;
                    int pc = prev.second;

                    int from_sq = get_square_number(pr, pc);
                    int to_sq = get_square_number(row, col);

                    // Ladders go up, snakes go down
                    if (isupper(c)) {
                        teleport[min(from_sq, to_sq)] = max(from_sq, to_sq);
                    } else {
                        teleport[max(from_sq, to_sq)] = min(from_sq, to_sq);
                    }
                } else {
                    seen[c] = {row, col};
                }
            }
        }
    }

    // Start at (n-1, 0) — bottom left
    int row = n - 1, col = 0;

    // Apply teleport at starting position
    int sq = get_square_number(row, col);
    if (teleport.count(sq)) tie(row, col) = get_coordinates(teleport[sq]);

    for (int i = 0; i < m; ++i) {
        int roll;
        cin >> roll;
        tie(row, col) = move_forward(row, col, roll);
        int sq = get_square_number(row, col);
        if (teleport.count(sq)) {
            tie(row, col) = get_coordinates(teleport[sq]);
        }
        if (get_square_number(row, col) == n * n) break;  // Win condition
    }

    cout << get_square_number(row, col) << '\n';
    return 0;
}
