#include <stdio.h>

int binsearch(int target, int array[], int length);

int main() {
    int test_arr[5] = {1,3,6,8,9};
    int target = 6;
    int n = 5; 
    
    printf("Found Target At Index: %d\n", binsearch(target, test_arr, n));
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid, saved_index;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) 
            high = mid - 1;
        else 
            low = mid + 1;
    }
    if (low < n && v[low] == x)
        return low;
    return -1;
}
