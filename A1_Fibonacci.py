
# Fibonacci Series using Recursive and Non-Recursive Methods

# Recursive Function
def fibonacci_recursive(n):
    if n <= 1:
        return n
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)


# Non-Recursive Function
def fibonacci_non_recursive(n):
    a, b = 0, 1

    for i in range(n):
        print(a, end=" ")
        a, b = b, a + b


# Main Program
print("FIBONACCI SERIES")
print("1. Non-Recursive Method")
print("2. Recursive Method")

choice = int(input("Enter your choice (1 or 2): "))
n = int(input("Enter the number of terms: "))

if n <= 0:
    print("Please enter a positive number.")

elif choice == 1:
    print("Fibonacci Series using Non-Recursive Method:")
    fibonacci_non_recursive(n)

elif choice == 2:
    print("Fibonacci Series using Recursive Method:")
    for i in range(n):
        print(fibonacci_recursive(i), end=" ")

else:
    print("Invalid choice!")

print()
