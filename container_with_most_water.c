#include <stdio.h>
#include <stdlib.h>

int maxArea(int* height, int heightSize)
{
    int start_index = 0;
    int end_index = heightSize -1;

    int max_area = 0;
    for(; start_index < end_index;)
    {
        int cur_height = height[start_index] > height[end_index] ? height[end_index] : height[start_index];
        int width = end_index - start_index;
        if(cur_height * width > max_area){
            max_area = cur_height * width;
        }
        if(height[start_index] > height[end_index])
        {
            -- end_index;
        }
        else
        {
            ++ start_index;
        }

    }
    return max_area;
}

int main(int argc,char* argv)
{
    int height[] = {1,8,6,2,5,4,8,3,7};
    int a = maxArea(height, 9);
    printf("max area = %d\n", a);
}