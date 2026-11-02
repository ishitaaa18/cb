# N-Queens Problem using Backtracking

def print_board(board, n):
    for i in range(n):
        for j in range(n):
            if board[i][j] == 1:
                print("Q", end=" ")
            else:
                print(".", end=" ")
        print()


# Check whether a Queen can be placed safely
def is_safe(board, row, col, n):

    # Check same column in previous rows
    for i in range(row):
        if board[i][col] == 1:
            return False

    # Check upper-left diagonal
    i = row - 1
    j = col - 1

    while i >= 0 and j >= 0:
        if board[i][j] == 1:
            return False
        i -= 1
        j -= 1

    # Check upper-right diagonal
    i = row - 1
    j = col + 1

    while i >= 0 and j < n:
        if board[i][j] == 1:
            return False
        i -= 1
        j += 1

    return True


# Solve using Backtracking
def solve_nqueens(board, row, n):

    # All Queens placed
    if row == n:
        return True

    # Try every column
    for col in range(n):

        if is_safe(board, row, col, n):

            # Place Queen
            board[row][col] = 1

            # Recursively place next Queen
            if solve_nqueens(board, row + 1, n):
                return True

            # Backtrack
            board[row][col] = 0

    return False


# Main Program
n = int(input("Enter number of Queens: "))

board = [[0 for _ in range(n)] for _ in range(n)]

if solve_nqueens(board, 0, n):
    print("\nN-Queens Solution:")
    print_board(board, n)
else:
    print("No solution exists.")