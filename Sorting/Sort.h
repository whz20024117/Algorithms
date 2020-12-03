#include <vector>
#include <iostream>

template<typename T>
class SortBase {

public:

    virtual void sort(std::vector<T>& arr) = 0;

    static bool isSorted(std::vector<T>& arr)
    {
        for (int i=0; i < arr.size() - 1; ++i)
        {
            if (arr[i] > arr[i+1]) return false;
        }
        return true;
    }

    static void printArray(std::vector<T>& arr)
    {
        for(auto& item : arr)
        {
            std::cout<<item<<", ";
        }
        std::cout << std::endl;
    }

    static void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
};