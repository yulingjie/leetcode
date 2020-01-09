#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class Solution {
public:
    int max_recur(vector<int>& nums, int l, int r)
    {
       cout<<"l = "<<l<<" r = "<<r<<endl;
       if (l == r) 
       {
        return nums[l];
       }
       int mid = (l + r + 1) /2; // upper limit
        cout<<"mid = "<<mid<<endl;
        int max_mid = nums[mid];
        int cur = max_mid;
        for(int i = mid-1; i >= l;--i)
        {
               cur+= nums[i];
            if(cur > max_mid)
            {
                max_mid = cur;
            }
        }
        cur=max_mid;
        for(int i = mid +1; i <= r; ++i)
        {
            cur += nums[i];
            if (cur > max_mid)
            {
                max_mid = cur;
            }
        }
        cout<<"max_mid = "<<max_mid<<endl;
        int max_l = INT_MIN;
        if (l < mid)
        {
            
            max_l = max_recur(nums, l ,mid-1);
        }
        int max_r = INT_MIN;
        if (mid  < r) 
        {
            max_r = max_recur(nums, mid + 1, r);
        }
        cout<<"max_l = "<<max_l<<" max_r = "<<max_r <<" max_mid = "<<max_mid<<endl;
        if (max_mid >= max_l && max_mid >= max_r)     
        {
            return max_mid;
        }
        if(max_l >= max_mid && max_l >= max_r)
        {
            return max_l;
        }
        if(max_r >= max_mid && max_r >= max_l)
        {
            return max_r;
        }
        return max_mid;
    }
    
    int maxSubArray(vector<int>& nums) {
       return max_recur(nums, 0, nums.size()-1) ;
    }
};
int main(void)
{
    Solution s;
    vector<int> nums = {0,-2,0};
    int ret = s.maxSubArray(nums);
    cout<< ret<<endl;
}
