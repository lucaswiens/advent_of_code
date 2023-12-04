#include "utility.h"

std::vector<std::string> Utility::split_string(const std::string& input, const std::string &delimiter) {
    std::vector<std::string> split;
    size_t last_position = 0;
    size_t position = input.find(delimiter);

    while (position != std::string::npos) {
        split.push_back(input.substr(last_position, position - last_position));
        last_position = position + delimiter.length();
        position = input.find(delimiter, last_position);
    }

    split.push_back(input.substr(last_position));
    return split;
}
