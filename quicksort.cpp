#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;

int partitionArray(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionArray(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int randomized_partition(vector<int>& arr, int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    swap(arr[random_index], arr[high]);
    return partitionArray(arr, low, high);
}

void randomized_quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomized_partition(arr, low, high);
        randomized_quick_sort(arr, low, pi - 1);
        randomized_quick_sort(arr, pi + 1, high);
    }
}

void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

int main() {
    vector<int> arr;
    int n, x;
    cout << "Enter number of array elements: "; cin >> n;
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) { cin >> x; arr.push_back(x); }

    vector<int> arr1 = arr;
    auto start = chrono::high_resolution_clock::now();
    if (!arr1.empty()) quick_sort(arr1, 0, (int)arr1.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    double deterministic_time = chrono::duration<double>(end - start).count();

    vector<int> arr2 = arr;
    srand((unsigned)time(nullptr));
    start = chrono::high_resolution_clock::now();
    if (!arr2.empty()) randomized_quick_sort(arr2, 0, (int)arr2.size() - 1);
    end = chrono::high_resolution_clock::now();
    double randomized_time = chrono::duration<double>(end - start).count();

    cout << "\nOriginal Array: "; printArray(arr);
    cout << "\nDeterministic Quick Sort:\nSorted Array: "; printArray(arr1);
    cout << "Execution Time: " << deterministic_time << " seconds\n";
    cout << "\nRandomized Quick Sort:\nSorted Array: "; printArray(arr2);
    cout << "Execution Time: " << randomized_time << " seconds\n";
    return 0;
}
