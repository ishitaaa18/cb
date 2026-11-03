#include <iostream>
#include <vector>
using namespace std;

void print_board(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] == 1 ? "Q " : ". ");
        cout << "\n";
    }
}

bool is_safe(const vector<vector<int>>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1) return false;

    int i = row - 1, j = col - 1;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 1) return false;
        i--; j--;
    }

    i = row - 1; j = col + 1;
    while (i >= 0 && j < n) {
        if (board[i][j] == 1) return false;
        i--; j++;
    }
    return true;
}

bool solve_nqueens(vector<vector<int>>& board, int row, int n) {
    if (row == n) return true;
    for (int col = 0; col < n; col++) {
        if (is_safe(board, row, col, n)) {
            board[row][col] = 1;
            if (solve_nqueens(board, row + 1, n)) return true;
            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of Queens: "; cin >> n;
    if (n <= 0) {
        cout << "Please enter a positive number.\n";
    } else if (n == 1) {
        cout << "\nN-Queens Solution:\nQ\n";
    } else if (n == 2 || n == 3) {
        cout << "No solution exists.\n";
    } else {
        vector<vector<int>> board(n, vector<int>(n, 0));
        board[0][1] = 1; // Same fixed first queen as the Python program
        if (solve_nqueens(board, 1, n)) {
            cout << "\nN-Queens Solution:\n";
            print_board(board, n);
        } else {
            cout << "No solution exists with the first Queen fixed.\n";
        }
    }
    return 0;
}
