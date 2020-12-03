/*
Merge sort:
    - Stable
    - Require O(n) space complexity
    - Guarantee O(Nlogn) time complexity
    - Can be very useful for linked list sorting. Although the implementation can be very different

*/

#include "Sort.h"

class MergeSort: public SortBase<int>
{
    void merge(std::vector<int>& arr, int low, int mid, int high)
    {
        int nl = mid - low + 1;
        int nh = high - mid;
        std::vector<int> left;
        std::vector<int> right;

        for (int i=0; i<nl; ++i)
        {
            left.push_back(arr[low + i]);
        }

        for (int i=0; i<nh; ++i)
        {
            right.push_back(arr[mid + i + 1]);
        }

        int p1 = 0; //pointer for left
        int p2 = 0; //pointer for right
        int p = low;    //pointer for arr

        while (p1 < left.size() && p2 < right.size())
        {
            if (left[p1] <= right[p2])
            {
                arr[p] = left[p1];
                p1++;
                p++;
            }
            else
            {
                arr[p] = right[p2];
                p2++;
                p++;
            }  
        }

        while (p1 < left.size())
        {
            arr[p] = left[p1];
            p++;
            p1++;
        }

        while (p2 < right.size())
        {
            arr[p] = right[p2];
            p++;
            p2++;
        }
    }

    void sort(std::vector<int>& arr, int low, int high)
    {
        if (low >= high) return;    //base case

        int mid = (low + high) / 2;

        sort(arr, low, mid);
        sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
public:

    void sort(std::vector<int>& arr) override
    {
        sort(arr, 0, arr.size() - 1);
    }

};


int main()
{
    std::vector<int> a{22,13,7,57,89,32,40,61};

    MergeSort alg = MergeSort();
    alg.sort(a);
    alg.printArray(a);

    return 0;
}