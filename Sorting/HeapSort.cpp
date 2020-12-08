/*
Heap Sort:
    - Natively not stable
    - Time complexity is O(nlogn). Heapify is O(logn) and needs to heapify n times in the main loop.
    - Not as good as merge sort and quick sort in practice, but can be useful when quick sort/merge sort
        recursive is too deep.
    

*/

#include "Sort.h"

class HeapSort: public SortBase<int>
{
    void heapify(std::vector<int>& arr, int n, int i)
    {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < n && arr[left] > arr[largest])
        {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
public:

    void sort(std::vector<int>& arr) override
    {
        for (int i = arr.size() / 2; i >= 0; --i)
        {
            heapify(arr, arr.size(), i);
        }

        for (int i = arr.size() - 1; i>=0; --i)
        {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

};


int main()
{
    //std::vector<int> a{22,13,7,57,89,32,40,61};
    std::vector<int> a{3,2,3,1,2,4,5,5,6};


    HeapSort alg = HeapSort();
    alg.sort(a);
    alg.printArray(a);

    return 0;
}