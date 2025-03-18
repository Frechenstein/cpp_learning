#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

/*
CPP program to find the most common element in an array.
*/

/**
 * Finds the most common element in an array using a counter.
 * 
 * For this algorithm to work, the array must contain the most 
 * common element for over half the elements.
 * 
 * Takes O(n) time and O(1) space.
 */
int mostCommonOverHalf(vector<int>& arr) {
    cout << "This algorithm only works, if the element to search occupies more than half of the array" << endl;
    
    auto start = chrono::high_resolution_clock::now();
    int mostCommonElement;
    int comp = 0;

    for(int i = 0; i < arr.size(); i++) {
        int element = arr[i];

        if (comp == 0) {
            mostCommonElement = element;
            comp++; 
        } else {
            if(mostCommonElement == element) {
                comp++;
            } else {
                comp--;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    duration *= 1e-9;

    if(comp == 0) {
        cout << "No element exists which occupies more than half of the array" << endl;
        cout << "Time elapsed: " << duration << endl;
        cout << endl;
        return 0;
    } else {
        cout << "The most common element in the array is: " << mostCommonElement << endl;
        cout << "Time elapsed: " << duration << endl;
        cout << endl;
        return mostCommonElement;
    }
};

/**
 * Can find the most common element in any array using nested loops.
 * Takes O(n^2) time and O(1) space.
 */
int mostCommonNaive(vector<int>& arr) {
    auto start = chrono::high_resolution_clock::now();
    int n = arr.size();
    int maxcount = 0;
    int res;

    for(int i = 0; i < n; i++) {
        int count = 0;
        for(int j = 0; j < n; j++){
            if (arr[i] == arr[j]) count++;
        }

        if(count > maxcount) {
            maxcount = count;
            res = arr[i];
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    duration *= 1e-9;

    cout << "The most common element is: " << res << endl;
    cout << "Time elapsed: " << duration << endl;
    cout << endl;
    return res;
};

/**
 * Prints all elements of an vector.
 */
void printVector(vector<int>& arr) {
    for(int element : arr) {
        cout << element << " ";
    }
    cout << endl;
};


int main() {

    vector<int> arr1 = {2, 2, 3, 4, 2, 2, 2, 5, 2, 3, 4, 2, 5};
    vector<int> arr2 = {7, 5, 7, 5, 8, 6, 4, 3, 6, 3, 7, 2, 9};

    cout << endl;

    printVector(arr1);
    mostCommonOverHalf(arr1);

    printVector(arr2);
    mostCommonNaive(arr2);


    return 0;
}