/*
Given a set of non-negative integers, and a target value, 
determine if there is a subset of the given set with sum equal to given sum. 

{3,4,5,12,19} target =9
return true
*/

#include <iostream>
#include <vector>

// Using DP

// 2-d table DP
// Rows (i) are end of subarray of the input array
// Columns (j) are target value.
// Entries are whether the sub array ended by i have target sum j.
/* 
Therefore, if arr[j] < j, dp[i][j] is true when:
    1) subarray ended with i - 1 has subset with target j - arr[i]
    or 
    2) subarray ended with i - 1 alreday satisfies target j

else
    dp[i][j] = dp[i-1][j]

In the first case, since we need add the new element to the sum, so arr[j] < j

Initial cases: all entries j = 0 should be true.
We can also infer that all entries that j > 0 , i = 0 is false, because target cannot be
greater than 0 when subset is length 0.

*/


int main()
{
    std::vector<int> arr{0,2,3,5};
    int target = 5;

    // DP
    std::vector<std::vector<bool>> dp(arr.size() ,std::vector<bool>(target + 1, false));

    // Initial cases
    for (int i = 0; i < arr.size(); ++i)
    {
        dp[i][0] = true;
    }

    // Main loop
    for (int i = 1; i < arr.size(); ++i)
    {
        for (int j = 1; j < target + 1; ++j)
        {
            // case 1
            if (arr[i] <= j)
            {
                dp[i][j] = dp[i - 1][j - arr[i]] || dp[i-1][j];
            }
            else
            {
                // case 2
                dp[i][j] = dp[i-1][j];
            }
            
        }
    }

    std::cout << "Result: " << dp[arr.size() - 1][target] << std::endl;
    
    return 0;
    
}