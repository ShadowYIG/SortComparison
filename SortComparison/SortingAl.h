#pragma once
#include <vector>


class sortingAl
{
private:
    void QuickSort_2(int* array, int l, int r);
    void MaxHeapify(int* arr, int start, int end);
    void suffle(int* arr, const size_t length);
    int maxbit(int *arr, const size_t length);
public:
    /*
    long Insertion;//��������
    long Shell;//ϣ������
    long Bubble;//ð������
    long Quick;//��������
    long Selection;//��ѡ������
    long Heap;//������
    long Merge;//�鲢����
    long Counting;//��������
    long Radix;//��������
    long cocktail;//��β������
    long Bogo;//Bogo���򣨺�������
    
    */
    void Insertion_Sort(int* arr, const size_t length);
    void shell_sort(int* arr, const size_t length);
    void Bubble_Sort(int* arr, const size_t length);
    void QuickSort(int* arr, const size_t length);
    void Selection_Sort(int* arr, const size_t length);
    void HeapSort(int* arr, const size_t length);
    void Merge_sort(int* arr, const size_t length);
    //void counting_sort(int* arr, int* sorted_arr, const size_t length);
    //void radixSort(int* arr, int digit, const size_t length);
    void radixsort(int* arr, const size_t length);
    void cocktailSort(int* arr, const size_t length);
    void bogoSort(int* arr, const size_t length);

};
