#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* prefix;
} NumArray;


NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* obj = (NumArray*)malloc(sizeof(NumArray));
    obj->prefix = (int*)malloc(sizeof(int) * (numsSize + 1));
    obj->prefix[0] = 0;
    for(int i = 0; i < numsSize;i++){
        obj->prefix[i+1] = obj->prefix[i] + nums[i];
    }
    return obj;
}

int numArraySumRange(NumArray* obj, int left, int right) {
    return obj->prefix[right + 1] - obj->prefix[left];
}

void numArrayFree(NumArray* obj) {
    free(obj->prefix);
}
int main(){
    int n;
    scanf("%d", &n);
    int* nums = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n;i++){
        scanf("%d", &nums[i]);
    }
    NumArray* obj = numArrayCreate(nums, n);
    int q; // So luong truy van
    scanf("%d", &q);
    for(int i = 0; i < q; i++){
        int left, right;
        printf("Nhập left right cho truy vấn %d: ", i + 1);
        scanf("%d %d", &left, &right);
        printf("Sumrange(%d, %d) = %d\n", left, right, numArraySumRange(obj, left, right));
    }
    numArrayFree(obj);
    free(nums);
    return 0;
}
/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);
 
 * numArrayFree(obj);
*/
