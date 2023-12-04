#include <iostream>
#include <string>
#include <vector>

#include "../utility/utility.h"

void read_card(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
int get_number_of_wins(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, const int &);
int get_number_of_cards(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, const int &);
int shahrazad(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, const int &);

int main(int argc, char *argv[]) {
    std::vector<std::vector<int>> winning_numbers, numbers;
    read_card(winning_numbers, numbers);

    int points_part_1 = 0, points_part_2 = 0;
    for (int i = 0; i < numbers.size(); i++) {
        points_part_1 += get_number_of_wins(winning_numbers, numbers, i);
        points_part_2 += shahrazad(winning_numbers, numbers, i);
    }
    points_part_2 += numbers.size();

    std::cout << "Part 1 = " << points_part_1 << std::endl;
    std::cout << "Part 2 = " << points_part_2 << std::endl;

    return 0;
}

int shahrazad(std::vector<std::vector<int>> &winning_numbers, std::vector<std::vector<int>> &numbers, const int &index) {
    int number_of_cards = get_number_of_cards(winning_numbers, numbers, index);
    int number_of_games = number_of_cards;
    for (int i = index + 1; i < index + 1 + number_of_cards; i++) {
        number_of_games += shahrazad(winning_numbers, numbers, i);
    }
    return number_of_games;
}

int get_number_of_cards(std::vector<std::vector<int>> &winning_numbers, std::vector<std::vector<int>> &numbers, const int &index) {
    int number_of_wins = 0;
    for (int w : winning_numbers.at(index)) {
        for (int n : numbers.at(index)) {
            if (w == n) {
                number_of_wins++;
            }
        }
    }
    return number_of_wins;
}

int get_number_of_wins(std::vector<std::vector<int>> &winning_numbers, std::vector<std::vector<int>> &numbers, const int &index) {
    int number_of_wins = 1;
    for (int w : winning_numbers.at(index)) {
        for (int n : numbers.at(index)) {
            if (w == n) {
                number_of_wins = number_of_wins << 1;
            }
        }
    }
    number_of_wins = number_of_wins >> 1;
    return number_of_wins;
}

void read_card(std::vector<std::vector<int>> &winning_numbers, std::vector<std::vector<int>> &numbers) {
    std::string line;
    while (std::getline(std::cin, line)) {
        winning_numbers.push_back({});
        numbers.push_back({});
        line = line.substr(line.find(':') + 2);
        int split_position = line.find('|');

        for (std::string &number : Utility::split_string(line.substr(0, split_position), " ")) {
            if (number.empty()) { continue;}
            winning_numbers.back().push_back(std::stoi(number));
        }

        for (std::string &number : Utility::split_string(line.substr(split_position + 1), " ")) {
            if (number.empty()) { continue;}
            numbers.back().push_back(std::stoi(number));
        }
    }
}
