#include <iostream>
#include <vector>
using namespace std;

class Solution
{

        bool jump(vector<int>& nums,int start, int end, vector<int>& rt)
        {
            cout<<"jump start = "<<start <<" end = "<<end<<endl;
            if(end == start) return true;
            int sz = end - start ; 
            for(int i =1; i <= sz; ++i)
            {
                //cout<<" check i = "<<i<<endl;
                
                if(rt[end-i]< 0)
                {
                    if(nums[end-i] >= i)
                    {
                        if(jump(nums, start, end - i,rt))
                        {
                            //cout<<"check jump index = "<<end-i<<" = "<<nums[end-i]<<" success "<<endl;
                            rt[end-i] = 1;
                            return true;
                        }
                        else
                        {
                            rt[end-i] = 0;
                        }
                    }
                }
                else
                {
                    if(rt[end-i] ==1)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    public:
        bool canJump(vector<int>& nums)
        {
            vector<int> rt(nums.size(), -1);
            return jump(nums, 0,nums.size() -1,rt);
        }

    private:
        /* data */
};

int main(void)
{
    vector<int> nums = {2,3,1,1,4};    
    Solution s;
    bool rt = s.canJump(nums);
    if(rt)
    {
        cout<<"can jump "<<endl;
    }
    else
    {
        cout<<"cannot jump"<<endl;
    }
    return 0;
}
