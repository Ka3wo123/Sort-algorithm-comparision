#include <iostream>
#include <ctime>
#include <random>

#define SIZE (1<<30)
#define THREADS 64

using namespace std;

__global__ void quicksort(int *data, int start, int end, int threads) {
    if(start >= end) {
        return;
    }

    int pivot = start;
    int i = start + 1;
    int j = end - 1;

    while(i <= j) {
        while(data[i] < data[pivot]) i++;
        while(data[j] > data[pivot]) j--;

        if(i <= j) {
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
    }

    int temp = data[pivot];
    data[pivot] = data[j];
    data[j] = temp;

    if(i < end) {
        cudaStream_t s;
        cudaStreamCreateWithFlags(&s, cudaStreamNonBlocking);
        quicksort<<<1, threads, 0, s>>>(data, i, end, (end - i));
        cudaStreamDestroy(s);
    }

    if(j > start) {
        cudaStream_t s1;
        cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
        quicksort<<<1, threads, 0, s1>>>(data, start, j, (j - start));
        cudaStreamDestroy(s1);
    }
}


int main() {
    random_device rd;
    mt19937 random(rd());
    uniform_int_distribution<> bounds{1, 10};

    int *h_arr, *d_arr;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
        
    h_arr = new int[SIZE];

    cout << "Filling array with values...";
        
    for(int *ptr = h_arr; ptr < h_arr + SIZE; ptr++) {
        *ptr = bounds(random);
    }
    
    cout << "Finished." << endl;

    cout << "Sorting..." << endl;     
     
    // for(int i = 0; i < SIZE; i++) {
    //   cout << h_arr[i] << " ";
    // }
    // cout << endl;
    
    cudaMalloc(&d_arr, SIZE * sizeof(int));
    
    cudaMemcpy(d_arr, h_arr, SIZE * sizeof(int), cudaMemcpyHostToDevice);
        
    cudaEventRecord(start);
    quicksort<<<1, 1>>>(d_arr, 0, SIZE, THREADS);
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);
    
    cudaMemcpy(h_arr, d_arr, SIZE * sizeof(int), cudaMemcpyDeviceToHost);

    if(ms / 1000 > 1) {
      cout << "Time execution: " << ms/1000 << "s" << endl;
    } else {
      cout << "Time execution: " << ms << "ms" << endl;
    }

    cout << "Array size: " << SIZE;
    
    

    // for(int i = 0; i < SIZE; i++) {
    //   cout << h_arr[i] << " ";
    // }

    delete[] h_arr;
    cudaFree(d_arr);

    return 0;
}