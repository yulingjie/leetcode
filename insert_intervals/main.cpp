#include<iostream>
#include<vector>
using namespace std;

class Solution
{
    public:
        vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
        {
            
            // binsearch location
            int start = 0;
            int end = intervals.size() -1;
            int startIndex = -1;
            int endIndex = -1;
            while(start <= end)
            {
                int mid = (start + end) /2;
                if(intervals[mid][0] > newInterval[1])
                {
                   end = mid-1; 
                }
                else if(intervals[mid][1] < newInterval[0])
                {
                    start = mid +1;
                }
                else
                {
                    cout<<"local mid = "<<mid<<endl;
                    
                    // expand to left and right
                    for(int i = mid; i>= 0; --i)
                    {
                        startIndex = i;
                        if(intervals[i][1] < newInterval[0])
                        {
                            startIndex = i + 1;
                            break;
                        }
                    }
                    for(int i =mid; i <= intervals.size() -1; ++i)
                    {
                        endIndex= i;
                        if(intervals[i][0] > newInterval[1])
                        {
                            endIndex = i-1;
                            break;
                        }
                    }
                    break;
                }

            }

            cout<<"startIndex = "<<startIndex<<" endIndex = "<<endIndex<<endl;
            if(startIndex != -1 ||  endIndex != -1) 
            {

                vector<vector<int>> vec;
                for(int i = 0; i < startIndex; ++i)
                {
                    vec.push_back(vector<int>(intervals[i]));
                }
                if(startIndex >= 0 && startIndex < intervals.size())
                {
                    if(newInterval[0] > intervals[startIndex][0])
                    {
                        newInterval[0] = intervals[startIndex][0];
                    }
                    if(newInterval[1] < intervals[endIndex][1])
                    {
                        newInterval[1] = intervals[endIndex][1];
                    }

                }
                if(endIndex >= 0 && endIndex < intervals.size())
                {
                    if(newInterval[0] > intervals[startIndex][0])
                    {
                        newInterval[0] = intervals[startIndex][0];
                    }

                    if(newInterval[1] < intervals[endIndex][1])
                    {
                        newInterval[1] = intervals[endIndex][1];
                    }
                }
                vec.push_back(vector<int>(newInterval));
                for(int i =endIndex +1; i < intervals.size() ;++i)
                {
                    vec.push_back(vector<int>(intervals[i]));
                }

                return vec;

            }
            else
            {
                cout<<"insert at "<<start<<endl;
                intervals.insert(intervals.begin() + start,newInterval);
                return intervals;
            }

        }
};
int main(int argc, char* argv[])
{
    Solution s;
    vector<vector<int>> intervals=
    {
        {1,2},
        {3,5},
        {6,7},
        {8,10},
        {12,16}
    };
    vector<int> newInterval ={4,8};
    auto vec = s.insert(intervals, newInterval);

    for(int i = 0; i < vec.size(); ++i)
    {
        cout<<"["<<vec[i][0]<<","<<vec[i][1]<<"]"<<endl; 
    }

    vector<vector<int>> emp= {{1,5}};
    newInterval = {2,3};
    auto e = s.insert(emp, newInterval);
    for(int i = 0; i < e.size(); ++i)
    {
        cout<<"["<<e[i][0]<<","<<e[i][1]<<"]"<<endl; 
    }



}

