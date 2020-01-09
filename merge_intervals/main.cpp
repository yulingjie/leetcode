#include<vector>
#include <iostream>
#include<algorithm>
using namespace std;
class Solution
{
    struct SortVec
    {
        bool operator()(const vector<int>&lhs,const vector<int>& rhs)
        {
            return lhs[0] < rhs[0];
        }
    };
    public:
        vector<vector<int>> merge(vector<vector<int>> & intervals)
        {
            SortVec st;
            sort(intervals.begin(), intervals.end(), st);
            vector<vector<int>> vec;
            vec.push_back(intervals[0]);
            vector<int>& cur = vec[0];
            for(int i =1; i <intervals.size(); ++i)
            {
                if(cur[1] > intervals[i][0])
                {
                    if(cur[1] < intervals[i][1])
                    {
                        cur[1] = intervals[i][1];
                    }
                }
                else
                {
                   vec.push_back(intervals[i]); 
                   cur = vec[vec.size() -1]; 
                   cout<<"cur low = "<<cur[0]<<" cur high = "<<cur[1]<<endl;
                }
            }
            return vec;
        }

};
int main(int argc, char* argv[])
{
    Solution s;
    vector<vector<int>> intervals=
    {
        {1,3},
        {2,6},
        {8,10},
        {15,18}
    };
    vector<vector<int>> vec = s.merge(intervals);
    for(int i = 0; i < vec.size(); ++i)
    {
        cout<<"low = "<<vec[i][0]<<" high =  "<<vec[i][1]<<endl;
    }

}
