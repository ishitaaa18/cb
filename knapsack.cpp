#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "\nDP Table:\n";
    for (const auto& row : dp) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "\nMaximum value: " << dp[n][capacity] << "\n";

    int w = capacity;
    vector<int> selected;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w -= weights[i - 1];
        }
    }
    reverse(selected.begin(), selected.end());
    cout << "Selected Items: ";
    for (int item : selected) cout << item << " ";
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of items: "; cin >> n;
    vector<int> weights(n), values(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter weight of item " << i + 1 << ": "; cin >> weights[i];
        cout << "Enter value of item " << i + 1 << ": "; cin >> values[i];
    }
    int capacity;
    cout << "Enter knapsack capacity: "; cin >> capacity;
    knapsack(weights, values, capacity);
    return 0;
}
