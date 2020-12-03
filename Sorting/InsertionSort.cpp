/*
Insertion Sort
    - Stable
    - Online
    - In place sorting
    - Remark: Use when array is small or almost sorted. 
        Insertion sort takes almost no time (go through the array) when array is sorted.
        Insertion sort's worst case is when array is reverse sorted.

*/

#include "Sort.h"

class InsertionSort: public SortBase<int>
{
public:

    void sort(std::vector<int>& arr) override
    {
        if (isSorted(arr)) return;
        
        int current;
        int j;
        for (int i = 1; i < arr.size(); ++i)
        {
            current = arr[i];
            j = i - 1;
            while (j >= 0)
            {
                if (arr[j] > current) arr[j+1] = arr[j];
                else break;
                --j;
            }
            arr[j + 1] = current;
        }
    }

};


int main()
{
    std::vector<int> a{22,13,7,57,89,32,40,61};

    InsertionSort alg = InsertionSort();
    alg.sort(a);
    alg.printArray(a);

    return 0;
}