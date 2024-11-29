/*
    File Name : External.cpp
    Description : 알고리즘 HW5 과제 중 7.External algorithm 구현

    Input : matrix_input.txt 
    Output : external_output.txt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>
using namespace std;

// Insertion Sort Function
void insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Sort part from input file 
void process_part(ifstream& input_file, int part_size, int part_index, vector<int>& all_sorted_data) {
    // dynamic Allocation
    int* part_data = new int[part_size]; 
    if (!part_data) {
        cerr << "Memory allocation failed!" << endl;
        return;
    }

    int i = 0;


    while (i < part_size && input_file >> part_data[i]) {
        i++;
    }

    // Sort the part using Insertion Sort
    insertion_sort(part_data, i);

    // Add sorted data to the all_sorted_data vector
    for (int j = 0; j < i; ++j) {
        all_sorted_data.push_back(part_data[j]);
    }

    // Free dynamically allocated memory using delete
    delete[] part_data;
}

// Function to merge sorted parts into one final output file
void merge_parts(const vector<int>& all_sorted_data, const string& output_filename) {
    ofstream output_file(output_filename);

    // Write the sorted data to the output file
    for (size_t i = 0; i < all_sorted_data.size(); i++) {
        output_file << all_sorted_data[i] << endl;
    }

    output_file.close();
}

int main() {
    ifstream input_file("input.txt");
    if (!input_file) {
        cerr << "File Read Error" << endl;
        return 1;
    }

    const int MEMORY_SIZE = 100;  // in Memory Size
    const string OUTPUT_FILENAME = "external_output.txt";

    vector<int> all_sorted_data;
    int part_index = 0;

    while (!input_file.eof()) {
        process_part(input_file, MEMORY_SIZE, part_index++, all_sorted_data);
    }

    input_file.close();

    // Sort all data in memory
    insertion_sort(&all_sorted_data[0], all_sorted_data.size());

    // Merge parts
    merge_parts(all_sorted_data, OUTPUT_FILENAME);

    cout << "Save " << OUTPUT_FILENAME << endl;
    
    return 0;
}
