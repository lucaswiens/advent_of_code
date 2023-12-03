#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void read_grid(const std::string &, std::vector<std::vector<char>> &);
bool neighbor_is_symbol(const std::vector<std::vector<char>> &, const int &, const int &);
int get_gear_ratio(const std::vector<std::vector<char>> &, const int &, const int &);
std::pair<int, int> get_number_and_offset(const std::vector<char> &, const int &);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Specify the input file" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::vector<std::vector<char>> part_grid;
    read_grid(filename, part_grid);
    if (part_grid.empty()) { return 1;}
    // grid is padded
    int rows = part_grid.size() - 1;
    int columns = part_grid.at(0).size() - 1;
    int sum_of_parts = 0, sum_of_gear_ratios = 0;

    for (int row = 1; row < rows; row++) {
        for (int column = 1; column < columns; column++) {
            if (isdigit(part_grid.at(row).at(column)) && neighbor_is_symbol(part_grid, row, column)) {
                std::pair<int, int> number_and_offset = get_number_and_offset(part_grid.at(row), column);
                sum_of_parts += number_and_offset.first;
                column += number_and_offset.second;
            }

            if (part_grid.at(row).at(column) == '*') {
                sum_of_gear_ratios += get_gear_ratio(part_grid, row, column);
            }
        }
    }
    std::cout << "Sum of parts       = " << sum_of_parts << std::endl;
    std::cout << "Sum of gear ratios = " << sum_of_gear_ratios << std::endl;
    return 0;
}

int get_gear_ratio(const std::vector<std::vector<char>> &part_grid, const int &row, const int &column) {
    std::vector<int> gear_numbers;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (isdigit(part_grid.at(row + i).at(column + j))) {
                std::pair<int, int> number_and_offset = get_number_and_offset(part_grid.at(row + i), column + j);
                gear_numbers.push_back(number_and_offset.first);
                j += number_and_offset.second;
            }
        }
    }
    // gear ratio only defined for two gears
    if (gear_numbers.size() != 2) { return 0;}
    return gear_numbers.at(0) * gear_numbers.at(1);
}
std::pair<int, int> get_number_and_offset(const std::vector<char> &part_row, const int &column) {
    int index = 0, number = 0, offset = 0;
    while (isdigit(part_row.at(column - index))) {
        number = number + (part_row.at(column - index) - '0') * std::pow(10, index);
        index++;
    }

    index = 1;
    while (isdigit(part_row.at(column + index))) {
        number = number * 10 + (part_row.at(column + index) - '0');
        index++;
        offset++;
    }

    return {number, offset};
}

bool neighbor_is_symbol(const std::vector<std::vector<char>> &part_grid, const int &row, const int &column) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!isdigit(part_grid.at(row + i).at(column + j)) && part_grid.at(row + i).at(column + j) != '.') {
                return true;
            }
        }
    }
    return false;
}

void read_grid(const std::string &filename, std::vector<std::vector<char>> &part_grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    // include '.' padding to avoid boundary checks later
    std::string line;
    part_grid.push_back({});
    while (std::getline(file, line)) {
        part_grid.push_back({});
        part_grid.back().push_back('.');
        for (char c : line) {
            part_grid.back().push_back(c);
        }
        part_grid.back().push_back('.');
    }
    part_grid.push_back({});
    for (int i = 0; i < part_grid.at(1).size(); i++) {
        part_grid.at(0).push_back('.');
        part_grid.back().push_back('.');
    }

    file.close();
}
