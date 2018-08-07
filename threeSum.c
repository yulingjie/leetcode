#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


int* prepareData(int* nums, int numsSize, int* len, int* min)
{
    *min = INT_MAX;
    int max = INT_MIN;
    for(int i = 0; i < numsSize; ++i)
    {
        if(nums[i] < (*min))
        {
            *min = nums[i];
        }
        if(nums[i] > max)
        {
            max = nums[i];
        }
    }
    int max_len = max - *min + 1;
    int* arr = (int*)malloc(max_len * sizeof(int));
    memset(arr, 0, sizeof(int)*max_len);
    
    for(int i = 0; i< numsSize; ++i)
    {
        int n = nums[i] - *min;
        arr[n]++;
        
    }
    *len = max_len;
    return arr;
    
}
int twoSum(const int* const min_based_count_arr,  const int max_len, const int start_index, const int min,
 const int target, const int use_index, int*** pointer_rt_arr)
{
    *pointer_rt_arr = NULL;
    int rt_arr_len = 0;
    int * min_based_use_count_arr = (int*)malloc(sizeof(int)* max_len);
    memset(min_based_use_count_arr,0, sizeof(int)*max_len);
    min_based_use_count_arr[use_index] += 1;
    for(int n_index = start_index; n_index < max_len; ++n_index)
    {
        if(min_based_count_arr[n_index]<=0) continue;
        if(min_based_use_count_arr[n_index] >= min_based_count_arr[n_index]) continue;
        int n = n_index + min;
        int m = target - n;
        int m_index = m - min;
        if(m_index < n_index 
        || m_index >= max_len
        || (m_index == n_index && (min_based_count_arr[n_index] - min_based_use_count_arr[n_index]) < 2) 
        || (min_based_count_arr[m_index] <= min_based_use_count_arr[m_index]))
        {
            continue;
        }
        if(*pointer_rt_arr == NULL)
        {
            *pointer_rt_arr = (int**)malloc(sizeof(int*));
        }
        else
        {
            int** old_arr = *pointer_rt_arr;
            *pointer_rt_arr = (int**)malloc(sizeof(int*)* (rt_arr_len + 1));
            for(int j = 0; j != rt_arr_len; ++j)
            {
                (*pointer_rt_arr)[j] = old_arr[j];
            }
            free(old_arr);            
        }
        (*pointer_rt_arr)[rt_arr_len] = (int*)malloc(sizeof(int)*2);
        int* p_cur = (*pointer_rt_arr)[rt_arr_len];
        rt_arr_len ++;
        p_cur[0] = n;
        p_cur[1] = m;     
        min_based_use_count_arr[n_index]++;
        min_based_use_count_arr[m_index] ++ ;   
    }
    free(min_based_use_count_arr);
    return rt_arr_len;
}
int calculate(const int* const min_based_count_arr,const int max_len, const int min, int*** pointer_rt_arr)
{       
    int maxCount = 0;
    int ** rt_two_arr = NULL;
    int len = 0;    

    for(int i = 0; i < max_len; ++i)
    {
        if(min_based_count_arr[i] <= 0) continue;
        int n = i + min;
        int** two_arr = NULL;
        int count = twoSum(min_based_count_arr, max_len,i+1, min, 0- n, i,&two_arr);
        if(count > 0)
        {
            if(rt_two_arr == NULL)
            {            
                rt_two_arr = (int**)malloc(sizeof(int*)* count);            
            }    
            else
            {
                int** old_arr = rt_two_arr;
                rt_two_arr = (int**)malloc(sizeof(int*) *(len + count));
                for(int j = 0; j < len; ++j)
                {
                    rt_two_arr[j] = old_arr[j];
                }
                free(old_arr);
            }
            for(int j = 0; j < count ;++j)
            {
                rt_two_arr[j+ len] = (int*)malloc(sizeof(int)* 3);
                rt_two_arr[j+len][0] = two_arr[j][0];
                rt_two_arr[j+len][1] = two_arr[j][1];
                rt_two_arr[j+len][2] = n;
            }
            len += count;
        }
        if(min_based_count_arr[i]<2) continue;
        for(int j = i; j < max_len; ++j)
        {
            if(j == i && min_based_count_arr[j] <=2) continue;
            if(min_based_count_arr[j] <= 0) continue;
            if(j + min == 0 - n *2)
            {
                if(rt_two_arr == NULL)
                {
                    rt_two_arr = (int**)malloc(sizeof(int*)* 1);
                }
                else
                {
                    int** old_arr = rt_two_arr;
                    rt_two_arr = (int**)malloc(sizeof(int*) *(len + 1));
                    for(int j = 0; j < len; ++j)
                    {
                        rt_two_arr[j] = old_arr[j];
                    }
                    free(old_arr);
                }    
                rt_two_arr[len] = (int*)malloc(sizeof(int)* 3);
                rt_two_arr[len][0] =j + min;
                rt_two_arr[len][1] = rt_two_arr[len][2] = n;
                len +=1;
            }
        }
        
    }
    (* pointer_rt_arr) = rt_two_arr;
    return len;

}
int** threeSum(int* nums, int numsSize, int* return_size)
{   
    int len = 0;
    int min = INT_MAX;
    int* data = prepareData(nums, numsSize, &len, &min); 
    for(int i =0; i < len; ++i)
    {
        printf("%d ", data[i]);
    } 
    printf("\n");
    int** rt_arr = NULL;
    *return_size = calculate(data, len, min,&rt_arr);
    return rt_arr;
}
int compareFunc(const void *a ,const void *b)
{
    return (*(int*)a - *(int*)b);
}

int** threeSumQSort(int* nums, int numSize,int * len)
{
    int * sort_arr = (int*)calloc(numSize, sizeof(int));
    memcpy(sort_arr, nums, sizeof(int) * numSize);
    qsort(sort_arr, numSize, sizeof(int), compareFunc);
    int max = sort_arr[numSize - 1];
    if(max < 0)
    {
        return NULL;
    }
    int * num_base_count_arr = (int*)calloc(numSize, sizeof(int));
    for(int i = 0; i < numSize; ++i)
    {
        if(sort_arr[i] >= 0)
        {
            num_base_count_arr[sort_arr[i]]++;
        }
    }
    int max_return_arr_size = numSize * (numSize -1) * (numSize -2) / (3*2);
    int** ret_arr = (int**)calloc(max_return_arr_size, sizeof(int*));
    int** ret_arr_iter = ret_arr;
    *len = 0;
    for(int i = 0; i < numSize;++i)
    {   
        // find different num each turn
        if(i>0 && sort_arr[i] == sort_arr[i-1]) continue;
        // return when min num > 0
        if(sort_arr[i] > 0) break;
        for(int j = i+ 1;j< numSize;++j)
        {
            // find different num each turn
            if(j > i+1 && sort_arr[j] == sort_arr[j -1]) continue;
            
            if(sort_arr[i] + 2 * sort_arr[j] > 0) break;

            int need_num = 0 - (sort_arr[i] + sort_arr[j]);
            int need_count = 1;
            if(need_num == sort_arr[i]) ++need_count;
            if(need_num == sort_arr[j]) ++need_count;
            if(num_base_count_arr[need_num] >= need_count)
            {
                *ret_arr_iter = (int*)calloc(3, sizeof(int));
                (*ret_arr_iter)[0] = sort_arr[i];
                (*ret_arr_iter)[1] = sort_arr[j];
                (*ret_arr_iter)[2] = need_num;
                ++ret_arr_iter;
                ++(*len);
            }
        }
    }
    free(sort_arr);
    free(num_base_count_arr);
    return ret_arr;
}


int main(int argc, char* argv[])
{
    int arr[] = {0,0,0};
    int r;
    int** pr = threeSumQSort(arr, sizeof(arr)/sizeof(int), & r);
    for(int i =0; i < r; ++i)
    {
        for(int j = 0;j < 3; ++j)
        {
            printf("%d ", pr[i][j]);
        }
        printf("\n");
    }
}