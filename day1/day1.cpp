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
std::unique_ptr<std::vector<std::string>> readFileFromInput(std::string path) {
    std::ifstream file(path);
    auto lines = std::vector<std::string>();
    std::string linebuf;

    if (file.is_open()) {
        while(!file.eof()) {
            std::getline(file, linebuf);
            lines.push_back(linebuf);
        }
    }

    return std::make_unique<std::vector<std::string>>(lines);
}

/***
 * Compute the solution to part 1
 */
int partOne(std::unique_ptr<std::vector<std::string>> & lines) {
    auto depths = std::vector<int>();
    // Convert all of the strings to ints
    std::transform(
        lines->begin(), 
        lines->end(), 
        std::back_inserter(depths), 
        [] (std::string s) {return std::stoi(s);}
    );

    int num_increases = 0;
    // For every new measurement, we get the number of increases
    for (int i = 1; i < depths.size(); i++) {
        if (depths[i] > depths[i - 1]) {
            num_increases++;
        }
    }

    return num_increases;
}

/***
 * Compute the solution to part 2
 */
int partTwo(std::unique_ptr<std::vector<std::string>> & lines) {
    auto depths = std::vector<int>();
    // Convert all of the strings to ints
    std::transform(
        lines->begin(), 
        lines->end(), 
        std::back_inserter(depths), 
        [] (std::string s) {return std::stoi(s);}
    );


    int previous = -1; // Set to -1 to make it invalid
    int num_increases = 0;
    // For every new measurement, we get the number of increases
    for (int i = 2; i < depths.size(); i++) {
        int sliding_sum = depths[i] + depths[i - 1] + depths[i - 2];
        if (sliding_sum > previous) {
            // Don't count the first one
            if (previous != -1) {
                num_increases++;
            }
        }
        previous = sliding_sum;
    }

    return num_increases;
}

int main (int argc, char ** argv) {
    if (argc >= 2) {
        auto file_contents = readFileFromInput(std::string(argv[1]));
        std::cout << partOne(file_contents) << std::endl;
        std::cout << partTwo(file_contents) << std::endl;
    }
    return 0;
}