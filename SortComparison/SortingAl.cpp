#include "SortingAl.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void sortingAl::Insertion_Sort(int * arr, const size_t length) {
    if (length <= 1) {
        return;
    }
    else {
        for (int i = 1; i != length; i++) {
            int j = i - 1;
            int key = arr[i];
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
}


void sortingAl::shell_sort(int* arr, const size_t length) {
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                swap(arr[j], arr[j - h]);
            }
        }
        h = h / 3;
    }
}


void sortingAl::Bubble_Sort(int* arr, const size_t length) {
    for (int i = 0; i != length - 1; i++) {
        for (int j = 0; j + i != length - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}



void sortingAl::QuickSort_2(int* arr, int l, int r)
{
    if (l < r) {
        int i = l;
        int j = r;
        int tmp = arr[l];
        while (i < j) {
            while (i < j && arr[j] >= tmp) --j;
            if (i < j) {
                arr[i++] = arr[j];
            }
            while (i < j && arr[i] < tmp) ++i;
            if (i < j) {
                arr[j--] = arr[i];
            }

        }
        arr[i] = tmp;
        QuickSort_2(arr, l, i - 1);
        QuickSort_2(arr, i + 1, r);
    }
}

void sortingAl::QuickSort(int* arr, const size_t length)
{
    if (arr == NULL) {
        return;
    }
    if (length <= 0)
        return;
    QuickSort_2(arr, 0, length - 1);
}



void sortingAl::Selection_Sort(int* arr, const size_t length) {
    for (int i = 0; i != length; i++) {
        int min = i;
        for (int j = i + 1; j != length; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

//堆排序

void sortingAl::MaxHeapify(int *arr, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { 
        if (son + 1 <= end && arr[son] < arr[son + 1]) 
            son++;
        if (arr[dad] > arr[son])
            return;
        else { 
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void sortingAl::HeapSort(int *arr, const size_t length) {
    for (int i = length / 2 - 1; i >= 0; i--)
        MaxHeapify(arr, i, length - 1);
    for (int i = length - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        MaxHeapify(arr, 0, i - 1);
    }
}
//归并排序


void sortingAl::Merge_sort(int *arr, const size_t length) {
    int* a = arr;
    int* b = new int[length];
    for (int seg = 1; seg < length; seg += seg) {
        for (int start = 0; start < length; start += seg + seg) {
            int low = start, mid = min(start + seg, (int)length), high = min(start + seg + seg, (int)length);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        for (int i = 0; i < length; i++)
            b[i] = a[i];
        b = a;
    }
    delete[] b;
}




//基数排序
int sortingAl::maxbit(int *arr, const size_t length) //辅助函数，求数据的最大位数
{
    int maxData = arr[0];		///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < length; ++i)
    {
        if (maxData < arr[i])
            maxData = arr[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}


void sortingAl::radixsort(int *arr, const size_t length) 
{
    int d = maxbit(arr, length);
    int* tmp = new int[length];
    int* count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for (j = 0; j < length; j++)
        {
            k = (arr[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for (j = length - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (arr[j] / radix) % 10;
            tmp[count[k] - 1] = arr[j];
            count[k]--;
        }
        for (j = 0; j < length; j++) //将临时数组的内容复制到data中
            arr[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}


//鸡尾酒排序

void sortingAl::cocktailSort(int* arr, const size_t length)
{
    bool isSwap = true;
    size_t top = 0, bottom = length - 1, i;
    int temp;
    do {
        isSwap = false;
        // 从上到下比较. 
        for (i = top; i < bottom; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                isSwap = true;
            }
        }
        // 从下到上比较. 
        for (i = --bottom; i > top; --i)
        {
            if (arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                isSwap = true;
            }
        }
        ++top;
    } while (true == isSwap);
}


//Bogo排序

void sortingAl::suffle(int* arr, const size_t length)
{
    int i, r;
    for (i = 0; i < length - 1; i++)
    {
        r = rand() % (length - i);
        swap(arr[i], arr[r + i]);
    }
}
/* 排序过程 */


void sortingAl::bogoSort(int* arr, const size_t length)
{
    int i;
    int flag;
    srand((unsigned int)time(NULL));
    while (1)
    {
        flag = 0;
        for (i = 0; i < length - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                flag = 1;
                break;
            }
        }
        if (!flag) return;
        suffle(arr, length);
    }
}
