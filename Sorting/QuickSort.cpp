/*
Quick sort
    - Natively not stable;
    - In place in a generally. (does require extra memory during partitions)
    - Worst case: O(n^2) when the pivot is the largest (smallest) element when sorting acending(descending)
    - Very good performance in practice, because worst case rarelly happens and can be avoided easily
    - On average it is a O(nlogn) algorithm
    - Remarks:
        - If it is short array, insertion sort is better.
        - Quick sort is not good when the random access is expensive.
        - For linked list, Merge sort is better, because insertion in linked list require no extra memory.
        - The main advantage of Quick Sort over Merge sort is less space complexity.
        - Iterative solution can be carried out by using an auxiliary stack to mimic stack call of recursion.
        - Tail recursion for compiler optimization

*/

#include "Sort.h"


class QuickSort: public SortBase<int>
{
    int partition(std::vector<int>& arr, int low, int high)
    {
        // randomly pick a pivot
        int _p = rand() % (high - low) + low;
        const int pivot = arr[_p];
        // put the pivot at the end
        swap(arr[_p], arr[high]);

        int smaller = low - 1; // index of last element smaller than pivot

        for (int i = low; i < high; ++i) // high is pivot
        {
            if (arr[i] < pivot)
            {
                ++smaller;
                if (smaller == i) continue;
                else swap(arr[smaller], arr[i]);
            }
        }
        // move pivot at right position
        swap(arr[smaller + 1], arr[high]);
        return smaller + 1;
    }

    void sort(std::vector<int>& arr, int low, int high)
    {
        // Base case check
        if (low >= high) return;
        
        int pi = partition(arr, low, high);

        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
    }
public:

    void sort(std::vector<int>& arr) override
    {
        if (isSorted(arr)) return;

        sort(arr, 0, arr.size() - 1);

    }

};


int main()
{
    std::vector<int> a{22,13,7,57,89,32,40,61};

    QuickSort alg = QuickSort();
    alg.sort(a);
    alg.printArray(a);

    return 0;
}