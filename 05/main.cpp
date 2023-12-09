#include <cstddef>
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <map>

#include "../utility/utility.h"

class node {
public:
    node(const size_t &, const size_t &, const size_t &, const std::string &);
    size_t destination, source, range;
    std::string map_name;
};

node::node(const size_t &destination, const size_t &source, const size_t &range, const std::string &map_name): destination(destination), source(source), range(range), map_name(map_name) {}

void read_input(const std::istream &, std::vector<size_t> &, std::map<std::string, std::vector<node>> &, std::vector<std::string> &);
size_t get_location(std::vector<size_t>, const std::vector<std::string> &, const std::map<std::string, std::vector<node>> &);
size_t get_location_part2(std::vector<std::pair<size_t, size_t>>, const std::vector<std::string> &, const std::map<std::string, std::vector<node>> &);

int main() {

    std::vector<size_t> seed_values;
    std::vector<std::string> map_names;
    std::map<std::string, std::vector<node>> nodes;
    read_input(std::cin, seed_values, nodes, map_names);

    std::vector<std::pair<size_t, size_t>> seeds;
    for (size_t i = 0; i < seed_values.size(); i+=2) {
        seeds.push_back({seed_values.at(0), seed_values.at(1)});
    }

    size_t location_1 = get_location(seed_values, map_names, nodes);
    std::cout << "\nPart 1: " << location_1 << std::endl;
    size_t location_2 = get_location_part2(seeds, map_names, nodes);
    std::cout << "\nPart 2: " << location_2 << std::endl;
    return 0;
}

size_t get_location_part2(std::vector<std::pair<size_t, size_t>> seeds, const std::vector<std::string> &map_names, const std::map<std::string, std::vector<node>> &nodes) {
    return 0;
}

size_t get_location(std::vector<size_t> seeds, const std::vector<std::string> &map_names, const std::map<std::string, std::vector<node>> &nodes) {
    size_t location = std::numeric_limits<size_t>::max();
    for (size_t i = 0; i < seeds.size(); i++) {
        for (std::string map_name : map_names) { // map names is probably not needed
            for (node n : nodes.at(map_name)) {
                if (n.source <= seeds.at(i) && seeds.at(i) <= n.source + n.range) {
                    seeds.at(i) += n.destination - n.source;
                    break;
                }
            }
        }
    }
    for (const auto &d : seeds) {
    }

    location = *std::min_element(seeds.begin(), seeds.end());
    return location;
}

void read_input(const std::istream &input, std::vector<size_t> &locations, std::map<std::string, std::vector<node>> &nodes, std::vector<std::string> &map_names) {
    std::string line;
    std::getline(std::cin, line);
    for (std::string number : Utility::split_string(line.substr(line.find(":") + 2), " ")) {
        locations.push_back(std::stoul(number));
    }

    std::string map_name;
    while (std::getline(std::cin, line)) {
        if (line.empty()) { continue;}
        if (line.find("map") != std::string::npos) {
            map_name = line.substr(0, line.find(" "));
            map_names.push_back(map_name);
            nodes.insert({map_name, {}});
            continue;
        }

        std::vector<std::string> numbers = Utility::split_string(line, " ");
        nodes.at(map_name).push_back(node(std::stoul(numbers.at(0)), std::stoul(numbers.at(1)), std::stoul(numbers.at(2)), map_name));
    }
}
