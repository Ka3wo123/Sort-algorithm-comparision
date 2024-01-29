#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

using namespace std;


class SortAlgorithms
{

public:
    SortAlgorithms();

    template<typename T>
    string simple_bubble_sort(vector<T> &data);

    template<typename T>
    void simple_bubble_sort(vector<T> &data, int start, int end);

    template<typename T>
    string bubble_sort_multithread(vector<T> &data, int threads_number);

    template<typename T>
    string simple_quick_sort(vector<T> &data, int start, int end);

    template<typename T>
    string quick_sort_multithread(vector<T> &data, int threads_number);

};

SortAlgorithms::SortAlgorithms(){}


template<typename T>
string SortAlgorithms::simple_bubble_sort(vector<T> &data) {
    int size = data.size();

    for(int i = 0; i < size; ++i) {
        for(int j = i; j < size; ++j) {
            if (data[i] > data[j]) {
                swap(data[i], data[j]);
            }
        }
    }

    return "Simple bubble sort on single thread. Elements: " + to_string(data.size());
}

template<typename T>
void SortAlgorithms::simple_bubble_sort(vector<T> &data, int start, int end) {
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            if (data[i] > data[j]) {
                swap(data[i], data[j]);
            }
        }
    }        
}

template<typename T>
string SortAlgorithms::bubble_sort_multithread(vector<T> &data, int threads_number) {
    int size = data.size();
    int block_size = size / threads_number;

    vector<thread> threads;

    for (int i = 0; i < threads_number; ++i) {
        int start = i * block_size;
        int end = (i == threads_number - 1) ? size : (i + 1) * block_size;

        threads.emplace_back([this, &data, start, end]() {
            this->simple_bubble_sort(data, start, end);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int i = 1; i < threads_number; ++i) {
        int mid = i * block_size;
        inplace_merge(data.begin(), data.begin() + mid, data.end());
    }

    return "Bubble sort on " + to_string(threads_number) + " threads. Elements: " + to_string(data.size());
}

template<typename T>
string SortAlgorithms::simple_quick_sort(vector<T> &data, int start, int end) {
    if(start >= end) {
        return "";
    }

    int pivot = start;
    int i = start + 1;
    int j = end - 1;

    while(i <= j) {
        while(data[i] < data[pivot]) i++;
        while(data[j] > data[pivot]) j--;

        if(i <= j) {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    }

    swap(data[pivot], data[j]);

    if(i < end) {
        simple_quick_sort(data, i, end);
    }

    if(j > start) {
        simple_quick_sort(data, start, j);
    }

    return "Simple quicksort on single thread. Elements: " + to_string(data.size());
}

template<typename T>
string SortAlgorithms::quick_sort_multithread(vector<T> &data, int threads_number) {
    int size = data.size();
    int block_size = size / threads_number;

    vector<thread> threads;

    for (int i = 0; i < threads_number; ++i) {
        int start = i * block_size;
        int end = (i == threads_number - 1) ? size : (i + 1) * block_size;

        threads.emplace_back([this, &data, start, end]() {
            this->simple_quick_sort(data, start, end);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int i = 1; i < threads_number; ++i) {
        int mid = i * block_size;
        inplace_merge(data.begin(), data.begin() + mid, data.end());
    }

    return "Quick sort on " + to_string(threads_number) + " threads. Elements: " + to_string(data.size());
}


#endif // SORTALGORITHMS_H
