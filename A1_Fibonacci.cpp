#include <iostream>
using namespace std;

int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void fibonacci_non_recursive(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    cout << "FIBONACCI SERIES\n1. Non-Recursive Method\n2. Recursive Method\n";
    int choice, n;
    cout << "Enter your choice (1 or 2): "; cin >> choice;
    cout << "Enter the number of terms: "; cin >> n;
    if (n <= 0) cout << "Please enter a positive number.\n";
    else if (choice == 1) {
        cout << "Fibonacci Series using Non-Recursive Method:\n";
        fibonacci_non_recursive(n);
    } else if (choice == 2) {
        cout << "Fibonacci Series using Recursive Method:\n";
        for (int i = 0; i < n; i++) cout << fibonacci_recursive(i) << " ";
    } else cout << "Invalid choice!\n";
    cout << endl;
    return 0;
}
