# 0-1 Knapsack using Dynamic Programming

def knapsack(weights, values, capacity):

    n = len(weights)

    # Create DP table
    dp = [[0 for x in range(capacity + 1)]
          for y in range(n + 1)]

    # Build DP table
    for i in range(1, n + 1):
        for w in range(1, capacity + 1):

            if weights[i - 1] <= w:

                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                )

            else:
                dp[i][w] = dp[i - 1][w]

    # Display DP table
    print("\nDP Table:")
    for row in dp:
        print(row)

    # Maximum value
    print("\nMaximum value:", dp[n][capacity])

    # Find selected items
    w = capacity
    selected_items = []

    for i in range(n, 0, -1):
        if dp[i][w] != dp[i - 1][w]:
            selected_items.append(i)
            w -= weights[i - 1]

    print("Selected Items:", selected_items)


# Main Program
n = int(input("Enter number of items: "))

weights = []
values = []

for i in range(n):
    weight = int(input(f"Enter weight of item {i + 1}: "))
    value = int(input(f"Enter value of item {i + 1}: "))

    weights.append(weight)
    values.append(value)

capacity = int(input("Enter knapsack capacity: "))

knapsack(weights, values, capacity)