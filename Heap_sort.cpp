#include <iostream>
using namespace std;


void maxHeapify(int arr[], int n, int i) 
{
    int root = i;        
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    
    if (left < n && arr[left] > arr[root]) 
    {
        root = left;
    }

    
    if (right < n && arr[right] > arr[root]) 
    {
        root = right;
    }

    
    if (root != i) 
    {
        swap(arr[i], arr[root]);  
        maxHeapify(arr, n, root); 
    }
}


void buildMaxHeap(int arr[], int n)
{
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        maxHeapify(arr, n, i);
    }
}


void heapSort(int arr[], int n)
{
    buildMaxHeap(arr, n);  

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]); // Move current root to the end
        maxHeapify(arr, i, 0); 
    }
}


void printArray(int arr[], int n)
{
    cout << "[";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << "]";
    cout << endl;
}


int main()
{
    int arr[] = { 4, 10, 1, 8, 3, 6, 9, 2, 5,7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original Array: ";
    printArray(arr, n);

    heapSort(arr, n);

    cout << "Sorted Array: ";
    printArray(arr, n);

    return 0;
}


