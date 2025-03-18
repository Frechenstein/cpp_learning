#include <iostream>
#include <vector>
#include "Sorter.h"

using namespace std;

int main() {

    vector<int> arr = {12, 2, 4, 8, 11, 15, 3};

    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    Sorter sorter;
    sorter.quickSort(arr);

    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}