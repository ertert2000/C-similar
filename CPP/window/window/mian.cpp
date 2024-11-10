#include <iostream>
#include <vector>

class Tensor {
public:
    std::vector<std::vector<int>> data;

    Tensor(int rows, int cols) {
        data.resize(rows, std::vector<int>(cols));
    }

    void applyCondition(int threshold) {
        for (auto& row : data) {
            for (auto& el : row) {
                if (el < threshold) {
                    el = 0; // Пример условия: если значение меньше threshold, ставим его равным 0
                }
            }
        }
    }

    void print() {
        for (const auto& row : data) {
            for (int el : row) {
                std::cout << el << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Tensor tensor(3, 3);
    tensor.data = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    std::cout << "Original Tensor:\n";
    tensor.print();

    // Применяем условие: элементы меньше 5 заменяем на 0
    tensor.applyCondition(5);

    std::cout << "Modified Tensor:\n";
    tensor.print();

    return 0;
}
