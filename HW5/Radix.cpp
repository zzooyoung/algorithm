/*
    File Name : Radix.cpp
    Description : 알고리즘 HW5 과제 중 6. Radix Sorting algorithm 구현

    Input : input.txt
    Output1 : radix_lsd_output.txt
    Output2 : redix_msd_output.txt
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// return position number
int get_digit(int num, int digit_pos) {
    return (num / static_cast<int>(pow(10, digit_pos))) % 10;
}

// MSD Radix Sort helper function
void radix_msd_helper(vector<int>& arr, int low, int high, int digit_pos) {
    if (low >= high || digit_pos < 0) return;
    
    vector<vector<int>> buckets(10);
    
    // Distribute the numbers into the corresponding digit buckets
    for (int i = low; i <= high; ++i) {
        int digit = get_digit(arr[i], digit_pos);
        buckets[digit].push_back(arr[i]);
    }
    
    // Rebuild the array by merging the buckets in order
    int idx = low;
    for (int i = 0; i < 10; ++i) {
        for (int num : buckets[i]) {
            arr[idx++] = num;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (buckets[i].size() > 1) {
            radix_msd_helper(arr, low, low + buckets[i].size() - 1, digit_pos - 1);
        }
        low += buckets[i].size();
    }
}

// MSD Radix Sort
void radix_msd_sort(vector<int>& arr) {
    int max_num = *max_element(arr.begin(), arr.end());
    int max_digit_pos = 0;
    
    // Find the maximum 
    while (max_num > 0) {
        max_num /= 10;
        max_digit_pos++;
    }
    
    // Start sorting from the most digit
    radix_msd_helper(arr, 0, arr.size() - 1, max_digit_pos - 1);
}

// LSD Radix Sort
void radix_lsd_sort(vector<int>& arr) {
    int max_num = *max_element(arr.begin(), arr.end());
    int max_digit_pos = 0;

    // Find the maximum 
    while (max_num > 0) {
        max_num /= 10;
        max_digit_pos++;
    }

    for (int digit_pos = 0; digit_pos < max_digit_pos; ++digit_pos) {

        vector<vector<int>> buckets(10);


        for (int num : arr) {
            int digit = get_digit(num, digit_pos);
            buckets[digit].push_back(num);
        }

        // Rebuild the array
        int idx = 0;
        for (int i = 0; i < 10; ++i) {
            for (int num : buckets[i]) {
                arr[idx++] = num;
            }
        }
    }
}

int main() {
    // Read input data from input.txt
    ifstream input_file("input.txt");
    vector<int> arr;
    int num;
    
    // Read int from input file
    while (input_file >> num) {
        arr.push_back(num);
    }

    input_file.close();

    // MSD Radix Sort
    vector<int> arr_msd = arr; // Copy original array 
    radix_msd_sort(arr_msd);

    // Write Result to radix_msd_output.txt
    ofstream output_msd_file("radix_msd_output.txt");
    for (int i = 0; i < arr_msd.size(); ++i) {
        output_msd_file << arr_msd[i] << "\n";
    }
    output_msd_file.close();

    // LSD Radix Sort
    vector<int> arr_lsd = arr; // Copy original array
    radix_lsd_sort(arr_lsd);

    // Write result to radix_lsd_output.txt
    ofstream output_lsd_file("radix_lsd_output.txt");
    for (int i = 0; i < arr_lsd.size(); ++i) {
        output_lsd_file << arr_lsd[i] << "\n";
    }
    output_lsd_file.close();

    return 0;
}
