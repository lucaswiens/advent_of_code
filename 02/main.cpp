#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> split_string(const std::string &, const std::string &);
bool is_valid_game(const std::string &, const std::map<std::string, int> &);
int get_game_power(const std::string &);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Specify the input file" << std::endl;
        return 1;
    }
    std::string filename = argv[1];

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return 1;
    }

    std::map<std::string, int> color_number = {
        {"red",   12},
        {"green", 13},
        {"blue",  14},
    };

    int valid_game_sum = 0, power_game_sum = 0;
    std::string line;
    while (std::getline(file, line)) {
        size_t space_position = line.find(" ");
        int game_id = std::stoi(line.substr(space_position, line.find(":") - space_position));
        std::string game_string = line.substr(line.find(":") + 2, line.length());
        if (is_valid_game(game_string, color_number)) {
            valid_game_sum += game_id;
        }

        power_game_sum += get_game_power(game_string);
    }
    std::cout << "The sum of valid game ids = \n" << valid_game_sum << std::endl;
    std::cout << "The power of all games = \n" << power_game_sum << std::endl;
    return 0;
}

bool is_valid_game(const std::string &game_string, const std::map<std::string, int> &color_number) {
    std::vector<std::string> pulls = split_string(game_string, "; ");
    for (std::string pull : pulls) {
        std::vector<std::string> cubes = split_string(pull, ", ");
        for (std::string cube : cubes) {
            std::vector<std::string> number_and_color = split_string(cube, " ");
            int number_of_cubes = std::stoi(number_and_color.at(0));
            if (color_number.at(number_and_color.at(1)) < number_of_cubes) {
                return false;
            }
        }
    }
    return true;
}

int get_game_power(const std::string &game_string) {
    std::vector<std::string> pulls = split_string(game_string, "; ");
    //int red = 0, green = 0, blue = 0;
    std::map<std::string, int> color_min = {
        {"red",   0},
        {"green", 0},
        {"blue",  0},
    };

    for (std::string pull : pulls) {
        std::vector<std::string> cubes = split_string(pull, ", ");
        for (std::string cube : cubes) {
            std::vector<std::string> number_and_color = split_string(cube, " ");
            int number_of_cubes = std::stoi(number_and_color.at(0));
            if (color_min.at(number_and_color.at(1)) < number_of_cubes) {
                color_min.at(number_and_color.at(1)) = number_of_cubes;
            }
        }
    }
    return color_min.at("red") * color_min.at("green") * color_min.at("blue");
}

std::vector<std::string> split_string(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> split;
    size_t last_position = 0;
    size_t position = str.find(delimiter);

    while (position != std::string::npos) {
        split.push_back(str.substr(last_position, position - last_position));
        last_position = position + delimiter.length();
        position = str.find(delimiter, last_position);
    }

    split.push_back(str.substr(last_position, str.length()));
    return split;
}

