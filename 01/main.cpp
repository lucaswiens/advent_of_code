#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

size_t get_first_and_last_digit(const std::string &, const std::map<std::string, size_t> &);
size_t calibrate_passwort(const std::string &, const std::map<std::string, size_t> &);
bool is_valid_char(const std::string &, const size_t &);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Specify the input file" << std::endl;
        return 1;
    }

    std::map<std::string, size_t> valid_digits = {
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
    };

    std::string filename = argv[1];

    std::cout << "Part 1:\n"      << calibrate_passwort(filename, valid_digits)              << std::endl;

    valid_digits.insert({"one",   1});
    valid_digits.insert({"two",   2});
    valid_digits.insert({"three", 3});
    valid_digits.insert({"four",  4});
    valid_digits.insert({"five",  5});
    valid_digits.insert({"six",   6});
    valid_digits.insert({"seven", 7});
    valid_digits.insert({"eight", 8});
    valid_digits.insert({"nine",  9});

    std::cout << "Part 2:\n" << calibrate_passwort(filename, valid_digits) << std::endl;
    return 0;
}

size_t calibrate_passwort(const std::string &filename, const std::map<std::string, size_t> &valid_digits) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return 1;
    }

    size_t calibration = 0;
    std::string line;
    while (std::getline(file, line)) {
        calibration += get_first_and_last_digit(line, valid_digits);
    }

    file.close();
    return calibration;
}

size_t get_first_and_last_digit(const std::string &line, const std::map<std::string, size_t> &valid_digits) {
    size_t first = 0,
        last = 0,
        min_index = std::string::npos,
        max_index = 0;
    for (std::pair<std::string, size_t> key_value :  valid_digits) {
        size_t position = line.find(key_value.first);
        while (position != std::string::npos) {
            if (position <= min_index) {
                first  = key_value.second;
                min_index = position;
            }
            if (max_index <= position) {
                last = key_value.second;
                max_index = position;
            }

            position = line.find(key_value.first, position + 1);
        }
    }
    return first * 10 + last;
}
