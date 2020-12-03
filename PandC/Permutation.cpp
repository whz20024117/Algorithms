#include <iostream>

using namespace std;

void permute(string str, int left, int right)
{
    // base case
    if (left == right)
    {
        cout << str << endl;
        return;
    }

    for (int i = left; i < right; ++i)
    {
        swap(str[i], str[left]);
        permute(str, left + 1, right);
        swap(str[i], str[left]); //swap back
    }
}

int main()
{
    string str = "ABC";
    permute(str, 0, str.length());
}