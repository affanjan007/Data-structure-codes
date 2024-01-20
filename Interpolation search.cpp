#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            if (arr[left] == target) {
                return left;
            }
            return -1; // Element not found
        }

        // Estimate the position of the target element
        int pos = left + ((double)(right - left) / (arr[right] - arr[left])) * (target - arr[left]);

        if (arr[pos] == target) {
            return pos; // Found the element
        }
        if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }

    return -1; // Element not found
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 14;
    int result = interpolationSearch(arr, size, target);

    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }

    return 0;
}
