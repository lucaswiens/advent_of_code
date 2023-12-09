#include <algorithm>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

#include "../utility/utility.h"


void read_input(const std::istream &, std::vector<std::vector<int>> &);
void get_diffs(const std::vector<int> &, std::vector<std::vector<int>> &);
int predict_next(const std::vector<int> &, const std::vector<std::vector<int>> &);
int predict_prev(const std::vector<int> &, const std::vector<std::vector<int>> &);
bool is_zero(const std::vector<int> &);

int main() {
    std::vector<std::vector<int>> histories;
    read_input(std::cin, histories);

    int part1 = 0, part2 = 0;
    for (const std::vector<int> &history : histories) {
        std::vector<std::vector<int>> diffs;
        get_diffs(history, diffs);
        int next = predict_next(history, diffs);
        int prev = predict_prev(history, diffs);
        part1 += next;
        part2 += prev;
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
    return 0;
}

int predict_prev(const std::vector<int> &history, const std::vector<std::vector<int>> & diffs) {
    int prev = 0;
    for (size_t i = diffs.size() - 1; i > 0; i--) {
        prev = diffs.at(i - 1).at(0) - prev;
    }
    return history.at(0) - prev;
}

int predict_next(const std::vector<int> &history, const std::vector<std::vector<int>> & diffs) {
    int next = 0;
    for (size_t i = diffs.size() - 1; i > 0; i--) {
        next += diffs.at(i - 1).back();
    }
    return history.back() + next;
}

void get_diffs(const std::vector<int> &history, std::vector<std::vector<int>> &diffs) {
    diffs.push_back({});
    for (size_t i = 0; i < history.size() - 1; i++) {
        diffs.back().push_back(history.at(i + 1) - history.at(i));
    }

    bool all_zeroes = is_zero(diffs.back());
    size_t diff_last = 0;
    while (!all_zeroes) {
        diff_last = diffs.size() - 1;
        diffs.push_back({});

        for (size_t i = 0; i < diffs.at(diff_last).size() - 1; i++) {
            diffs.back().push_back(diffs.at(diff_last).at(i + 1) - diffs.at(diff_last).at(i));
        }

        all_zeroes = is_zero(diffs.back());
    }
}

bool is_zero(const std::vector<int> &vector) {
    return std::all_of(vector.cbegin(), vector.cend(), [](int i) { return i == 0; });
}

void read_input(const std::istream &input, std::vector<std::vector<int>> &histories) {
    std::string line;
    while (std::getline(std::cin, line)) {
        histories.push_back({});
        for (std::string number_string :  Utility::split_string(line, " ")) {
            histories.back().push_back(std::stoi(number_string));
        }
    }
}
