#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value, index;
    double ratio;
};

struct Node {
    int level, profit, weight;
    double bound;
    vector<int> chosen;
};

struct CompareBound {
    bool operator()(const Node& a, const Node& b) const {
        return a.bound < b.bound; // Highest bound first
    }
};

// ---------------- DYNAMIC PROGRAMMING ----------------
void knapsackDP(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "\nDP Table:\n";
    for (const auto& row : dp) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }

    cout << "Maximum value = " << dp[n][capacity] << "\n";

    int w = capacity;
    vector<int> selected;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w -= weights[i - 1];
        }
    }
    reverse(selected.begin(), selected.end());

    cout << "Selected item numbers: ";
    for (int item : selected) cout << item << " ";
    cout << "\n";
}

// ---------------- BRANCH AND BOUND ----------------
double calculateBound(const Node& node, int n, int capacity,
                      const vector<Item>& items) {
    if (node.weight >= capacity) return node.profit;

    double bound = node.profit;
    int totalWeight = node.weight;
    int j = node.level + 1;

    // Add complete items while they fit
    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        bound += items[j].value;
        j++;
    }

    // Add fraction of the next item for the upper bound
    if (j < n)
        bound += (capacity - totalWeight) * items[j].ratio;

    return bound;
}

void knapsackBranchBound(vector<Item> items, int capacity) {
    int n = items.size();

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    priority_queue<Node, vector<Node>, CompareBound> pq;

    Node root;
    root.level = -1;
    root.profit = 0;
    root.weight = 0;
    root.chosen.assign(n, 0);
    root.bound = calculateBound(root, n, capacity, items);
    pq.push(root);

    int maxProfit = 0;
    vector<int> bestChosen(n, 0);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.bound <= maxProfit || current.level == n - 1)
            continue;

        int next = current.level + 1;

        // Branch 1: Include the next item
        Node include = current;
        include.level = next;
        include.weight += items[next].weight;
        include.profit += items[next].value;
        include.chosen[next] = 1;

        if (include.weight <= capacity && include.profit > maxProfit) {
            maxProfit = include.profit;
            bestChosen = include.chosen;
        }

        include.bound = calculateBound(include, n, capacity, items);
        if (include.weight <= capacity && include.bound > maxProfit)
            pq.push(include);

        // Branch 2: Exclude the next item
        Node exclude = current;
        exclude.level = next;
        exclude.bound = calculateBound(exclude, n, capacity, items);

        if (exclude.bound > maxProfit)
            pq.push(exclude);
    }

    cout << "\nMaximum value = " << maxProfit << "\n";
    cout << "Selected item numbers: ";
    for (int i = 0; i < n; i++)
        if (bestChosen[i]) cout << items[i].index << " ";
    cout << "\n";
}

// ---------------- MAIN PROGRAM ----------------
int main() {
    int n, capacity, choice;

    cout << "0/1 KNAPSACK\n";
    cout << "1. Dynamic Programming\n";
    cout << "2. Branch and Bound\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of items must be positive.\n";
        return 0;
    }

    vector<int> weights(n), values(n);
    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value of item " << i + 1 << ": ";
        cin >> weights[i] >> values[i];

        if (weights[i] <= 0 || values[i] < 0) {
            cout << "Weights must be positive and values non-negative.\n";
            return 0;
        }

        items[i].weight = weights[i];
        items[i].value = values[i];
        items[i].index = i + 1;
        items[i].ratio = (double)values[i] / weights[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Capacity cannot be negative.\n";
        return 0;
    }

    if (choice == 1) {
        cout << "\nUsing Dynamic Programming:\n";
        knapsackDP(weights, values, capacity);
    } else if (choice == 2) {
        cout << "\nUsing Branch and Bound:\n";
        knapsackBranchBound(items, capacity);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
