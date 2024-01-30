#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include "sortalgorithms.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>

#define NUM_THREADS 64
#define SIZE (1<<30)

using namespace std;
using namespace chrono;

int main() {
    random_device rd;
    mt19937 random(rd());
    uniform_int_distribution<> bounds{1, 100};
    fstream resultsFile;

    chrono::time_point< std::chrono::steady_clock > time_start, time_stop;
    chrono::duration< double, milli > delta_msec;

    vector<int> arr(SIZE);
    SortAlgorithms sa;
    string timeExe;
    string algotithmUsed;

    resultsFile.open("../sort_measurement/results.txt", ios::out | ios::app);

    if(!resultsFile.good()) {
        cout << "File opening failed";
        resultsFile.close();
        return 1;
    }

    cout << "Filling array with values...";
    for(auto &el : arr) {
        el = bounds(random);
    }  

//    for(int it = 0; it < arr.size(); it++) {
//        cout << arr[it] << " ";
//    }

    cout << "Finished." << endl;

    cout << "Sorting..." << endl;

    time_start = chrono::steady_clock::now();
//    algotithmUsed = sa.simple_bubble_sort(arr);
//    algotithmUsed = sa.bubble_sort_multithread(arr, NUM_THREADS);
    algotithmUsed = sa.quick_sort_multithread(arr, NUM_THREADS);
//    algotithmUsed = sa.simple_quick_sort(arr, 0, arr.size());

    time_stop = chrono::steady_clock::now();

    delta_msec = time_stop - time_start;

    if(delta_msec.count() / 1000 > 1) {
        delta_msec /= 1000;
        timeExe = "Time execution " + to_string(delta_msec.count()) + "s\n\n";
    } else {
        timeExe = "Time execution " + to_string(delta_msec.count()) + "ms\n\n";
    }

    cout << timeExe << '\n';

    resultsFile << algotithmUsed << "\n" << timeExe;

//    for(int it = 0; it < arr.size(); it++) {
//        cout << arr[it] << " ";
//    }

    resultsFile.close();

    return 0;
}

