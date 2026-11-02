
import random
import time

# Partition function
def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


# Deterministic Quick Sort
def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)

        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)


# Randomized Partition
def randomized_partition(arr, low, high):
    random_index = random.randint(low, high)

    arr[random_index], arr[high] = arr[high], arr[random_index]

    return partition(arr, low, high)


# Randomized Quick Sort
def randomized_quick_sort(arr, low, high):
    if low < high:
        pi = randomized_partition(arr, low, high)

        randomized_quick_sort(arr, low, pi - 1)
        randomized_quick_sort(arr, pi + 1, high)


# Main Program
arr = list(map(int, input("Enter array elements separated by spaces: ").split()))

arr1 = arr.copy()

start = time.time()
quick_sort(arr1, 0, len(arr1) - 1)
deterministic_time = time.time() - start

arr2 = arr.copy()

start = time.time()
randomized_quick_sort(arr2, 0, len(arr2) - 1)
randomized_time = time.time() - start

print("\nOriginal Array:", arr)

print("\nDeterministic Quick Sort:")
print("Sorted Array:", arr1)
print("Execution Time:", deterministic_time, "seconds")

print("\nRandomized Quick Sort:")
print("Sorted Array:", arr2)
print("Execution Time:", randomized_time, "seconds")
