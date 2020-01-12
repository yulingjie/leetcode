#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution {
    vector<int> factorial;
    void Factorial(int n)
    {
        factorial.push_back(1);
        for(int i =1; i<n; ++i) 
        {
            factorial.push_back(factorial[i-1]*i);
        }
        factorial.push_back(n * factorial[n-1]);
    }
    void permutation_recur(vector<int>& vec,
            vector<int>::iterator start,
            vector<int>::iterator end ,
            int k)
    {
        if(start >= end -1)
        {
            return;
        }
        int next = factorial[end - start - 1];
        cout<<"next = "<<next<<endl;
        int index = 0;
        for(vector<int>::iterator ite = start; ite < end; ++ite)
        {
            if(next < k)  
            {
                k = k - next;
                ++index;
            }
            else
            {
                break;
            }
        }

        //
        //cout<<" start = "<<*start<<endl;
        cout<<"swap "<<*start << " and "<< *( start + index)<<endl;

        swap(*start, *(start + index));
        printStr(vec);
        
        cout<<"sort"<<endl;
        vector<int>::iterator ite = start+index - 1;
        // sort
        for(ite = start+index-1;ite > start;--ite)
        {
            if(*(ite) > * (ite + 1))
            {
                swap(*ite, *(ite + 1));
            }
        }
        
        printStr(vec);

        

        permutation_recur(vec, start +1 , end,k); 
    }
    void printStr(const vector<int>& vec)
    {
        string str;
        for(int i =0; i < vec.size(); ++i)
        {
            str += (vec[i] + '0');
        }
        cout<<str<<endl;

    }
    public:
    string getPermutation(int n, int k) {
        Factorial(n);
        vector<int> vec;
        for(int i = 0; i < n;++i) 
        {
            vec.push_back(i+1);
        }
        permutation_recur(vec,vec.begin(), vec.end(), k);
        string str;
        for(int i = 0; i < n; ++i)
        {
            cout<<vec[i]<<" ";
            str += (vec[i] + '0');
        }
        cout<<endl;
        return str;

    }
};
int main(int argc, char* argv[])
{
    Solution s;
    string str = s.getPermutation(4,19);
    cout<<"str = "<<str<<endl;
}
