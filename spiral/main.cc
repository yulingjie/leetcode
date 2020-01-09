#include <iostream>
#include <vector>
using namespace std;
class Solution
{
    public:
        vector<int> spiralOrder(vector<vector<int>>& matrix)
        {
            vector<int> vec;
            int i = 0; 
            int j = 0;
            int n = matrix.size() * matrix[0].size();
            int wl = -1; 
            int wr = matrix[0].size();
            int ht = matrix.size();
            int hb = -1;
            int status = 0;
            const int RIGHT = 1;
            const int DOWN = 2;
            const int LEFT = 3;
            const int UP = 4;
            status = RIGHT;
            while(n > 0)
            {
               // cout<<"[i,j] = "<<"["<<i<<","<<j<<"]"<<endl;
                if(j > wl && j < wr && i > hb && i < ht)
                {
                    cout<<matrix[i][j]<<" ";
                }
                else
                {
                    cout<<"reach end"<<endl;
                    break;
                }


                // probe next
                bool bnext = false;
                if(status == RIGHT)
                {
                    bnext = j < wr-1;
                }
                else if(status == LEFT)
                {
                    bnext = j > wl +1;
                }
                else if(status == UP)
                {
                    bnext = i < ht -1;
                }
                else if(status == DOWN)
                {
                    bnext = i > hb +1;
                }
                if(bnext)
                {
                    if (status == RIGHT)
                    {
                        j++;
                    }
                    else if(status == LEFT)
                    {
                        j--;
                    }
                    else if(status == UP)
                    {
                        i ++;
                    }
                    else if(status == DOWN)
                    {
                        i--;
                    }
                }
                else
                {
                    cout<<"change direction ";
                    if(status == RIGHT)
                    {
                        status = UP;
                        hb = i;
                       // wr --;
                        i++;
                        cout<<" to UP ";
                    }
                    else if(status == LEFT)
                    {
                        status = DOWN;
                    //    wl++;
                        ht = i;
                        i--;

                        cout<<" to DOWN ";
                    }
                    else if(status == UP)
                    {
                        status = LEFT;
                        wr = j;
                        j--;
                        cout<< " to LEFT ";
                    }
                    else if(status == DOWN)
                    {
                        status = RIGHT;
                        wl = j;
                        j++;
                        cout << " to RIGHT ";
                    }
                    cout<<endl;
                }
                --n;

            }
            return vec;
        }

};

int main(int argc, char *argv[])
{
    vector<vector<int>> vec = {{1,2,3},
        {4,5,6},
        {7,8,9}};
    Solution s;
    s.spiralOrder(vec);
    return 0;
}
