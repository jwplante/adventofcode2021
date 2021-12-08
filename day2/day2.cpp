#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

/***
 * Reads a file from the given path, and returns the file
 * contents to a string
 */
std::vector<std::string> readFileFromInput(std::string path) {
    std::ifstream file(path);
    auto lines = std::vector<std::string>();
    std::string linebuf;

    if (file.is_open()) {
        while(!file.eof()) {
            std::getline(file, linebuf);
            lines.push_back(linebuf);
        }
    }

    return lines;
}

/***
 * Splits the input string into two parts, returns a tuple
 * with the direction and the depth as an int
 */
std::tuple<std::string, int> processLine(std::string line) {
    size_t space_loc = line.find(' ');
    auto ret_tuple = std::make_tuple(std::string(), 0);
    if (space_loc < line.size() - 1) {
        std::string left = line.substr(0, space_loc);
        std::string right = line.substr(space_loc + 1, line.size());
        ret_tuple = std::make_tuple(left, std::stoi(right));
    }
    return ret_tuple;
}

// Part 1 Solution
long partOne(std::vector<std::string> lines) {
    auto split_lines = std::vector<std::tuple<std::string, int>>();
    std::transform(lines.begin(), lines.end(), std::back_inserter(split_lines), processLine);

    long horizontal = 0L, depth = 0L;
    for (auto split_line : split_lines) {
        auto [direction, value] = split_line;
        if (direction == "up") {
            depth -= value;
        } else if (direction == "down") {
            depth += value;
        } else if (direction == "forward") {
            horizontal += value; 
        }
    }
    std::cout << "Final horizontal: " << horizontal << std::endl;
    std::cout << "Final depth: " << depth << std::endl;

    return horizontal * depth;
}

// Part 2 solution
long partTwo(std::vector<std::string> lines) {
    auto split_lines = std::vector<std::tuple<std::string, int>>();
    std::transform(lines.begin(), lines.end(), std::back_inserter(split_lines), processLine);

    long horizontal = 0L, depth = 0L, aim = 0L;
    for (auto split_line : split_lines) {
        auto [direction, value] = split_line;
        if (direction == "up") {
            aim -= value;
        } else if (direction == "down") {
            aim += value;
        } else if (direction == "forward") {
            horizontal += value; 
            depth += (aim * value);
        }
    }
    std::cout << "Final horizontal: " << horizontal << std::endl;
    std::cout << "Final depth: " << depth << std::endl;

    return horizontal * depth;
}


int main (int argc, char ** argv) {
    if (argc >= 2) {
        auto file_contents = readFileFromInput(std::string(argv[1]));
        std::cout << partOne(file_contents) << std::endl;
        std::cout << partTwo(file_contents) << std::endl;
    }
    return 0;
}