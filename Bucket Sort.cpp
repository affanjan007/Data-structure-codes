#include <iostream>
using namespace std;

int findMax(int arr[], int n) {
    int maxVal = arr[0];
	int numDigits = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    while (maxVal > 0) {
        numDigits++;
        maxVal = maxVal / 10;
    }

    return numDigits;
}

void bucketSort(int arr[], int n) {
    int digitPosition = 1;

    int i, bucketCount[10], digitValue, elementIndex;
    int numPasses = findMax(arr, n);

    for (int pass = 0; pass < numPasses; pass++) {
        for (i = 0; i < 10; i++)
            bucketCount[i] = 0;
            
        int buckets[10][n];

        for (i = 0; i < n; i++) {
            digitValue = (arr[i] / digitPosition) % 10;
            elementIndex = bucketCount[digitValue];
            buckets[digitValue][elementIndex] = arr[i];
            bucketCount[digitValue]++;
        }

        elementIndex = 0;
        for (i = 0; i < 10; i++) {
            for (int j = 0; j < bucketCount[i]; j++) {
                arr[elementIndex] = buckets[i][j];
                elementIndex++;
            }
        }
        digitPosition *= 10;
    }
}

int main() {
    int arr[] = {45, 67, 90, 32, 78, 76, 11, 50, 43, 84};
	int	n=10;
	
    bucketSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}