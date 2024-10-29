#include <iostream>
#include <vector>
#include <algorithm>

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
    // 입력 데이터
    double max_capacity = 40.0;
    std::vector<Item> items = {
        {'A', 10, 600000, 60000},  // 백금
        {'B', 15, 750000, 50000},  // 금
        {'C', 25, 100000, 4000},   // 은
        {'D', 50, 50000, 1000}     // 주석
    };
    
    // 단위 무게당 가치가 높은 순으로 정렬
    std::sort(items.begin(), items.end(), compare);

    double total_weight = 0.0;
    double total_value = 0.0;
    std::vector<std::pair<char, double>> result;

    // Fractional Knapsack 알고리즘
    for (auto &item : items) {
        if (total_weight + item.weight <= max_capacity) {
            // 물건 전체를 담을 수 있는 경우
            total_weight += item.weight;
            total_value += item.value;
            result.push_back({item.name, item.weight});
        } else {
            // 물건 일부만 담아야 하는 경우
            double remaining_weight = max_capacity - total_weight;
            total_weight += remaining_weight;
            total_value += remaining_weight * item.value_per_weight;
            result.push_back({item.name, remaining_weight});
            break;
        }
    }

    // 결과 출력
    std::cout << "Goods\tWeight of goods in knapsack\tValue of goods in knapsack\n";
    for (auto &res : result) {
        std::cout << res.first << "\t\t" << res.second << "\t\t\t\t" << res.second * items[res.first - 'A'].value_per_weight << "\n";
    }
    std::cout << "Sum\t\t" << total_weight << "\t\t\t\t" << total_value << "\n";

    return 0;
}
