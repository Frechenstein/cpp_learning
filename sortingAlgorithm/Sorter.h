#ifndef SORTER_H
#define SORTER_H

#include <vector>

class Sorter {
    public: 
        void quickSort(std::vector<int>& arr);
    
    private:
        void quickSort(std::vector<int>& arr, int low, int high);
        int partition(std::vector<int>& arr, int low, int high);
};

#endif