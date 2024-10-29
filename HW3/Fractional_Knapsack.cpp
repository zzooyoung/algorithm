/*
    File Name : Fractional_Knapsack.cpp
    Description : 알고리즘 HW3 과제 중 5. Fractional Knapsack algorithm 구현 입니다. 

    output: 아래와 같은 형태로 출력 (A: 백금, B: 금, C: 은, D: 주석)
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    char name;
    double weight;
    double value;
    double value_per_weight;
};

bool compare(Item a, Item b) { 
    return a.value_per_weight > b.value_per_weight;
}

int main() {
    // input data
    double max_capacity = 40.0;
    vector<Item> items = {
        {'A', 10, 600000, 60000},  // 백금
        {'B', 15, 750000, 50000},  // 금
        {'C', 25, 100000, 4000},   // 은
        {'D', 50, 50000, 1000}     // 주석
    };
    
    // value / weight
    sort(items.begin(), items.end(), compare);

    double total_weight = 0.0;
    double total_value = 0.0;
    vector<pair<char, double>> result;

    // Fractional Knapsack algorithm
    for (auto &item : items) {
        if (total_weight + item.weight <= max_capacity) {
            // a whole things
            total_weight += item.weight;
            total_value += item.value;
            result.push_back({item.name, item.weight});
        } else {
            // Fractional
            double remaining_weight = max_capacity - total_weight;
            total_weight += remaining_weight;
            total_value += remaining_weight * item.value_per_weight;
            result.push_back({item.name, remaining_weight});
            break;
        }
    }

    // print result
    cout << fixed << setprecision(0);  // set int type
    cout << "Goods\tWeight of goods in knapsack\tValue of goods in knapsack\n";
    for (auto &res : result) {
        char name = res.first;
        double weight = res.second;
        double value = weight * items[name - 'A'].value_per_weight;
        cout << name << "\t\t" << weight << "\t\t\t\t" << value << "\n";
    }
    cout << "Sum\t\t" << total_weight << "\t\t\t\t" << total_value << "\n";

    return 0;
}
