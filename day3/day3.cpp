#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

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
 * Given a string of 0s and 1s, add the occurances of each character to an accumulator
 * map, where the key is the bit position, the value is the occurences where there is a 1.
 */
void byteCount(std::map<int, int>& stats, std::string line) {
    for (int i = 0; i < line.size(); i++) {
        // We need to make the bit position such that the LSB is on the right
        int bit_position = line.size() - i - 1;
        if (line[i] == '1') {
            // Record the value
            if (stats.find(bit_position) != stats.end()) {
                stats[bit_position]++;
            } else {
                stats[bit_position] = 1;
            }
        }
    }
}

/***
 * Given strings of 0s and 1s, get the number of 1s at a given bit position.
 */
int countOnes(std::vector<std::string> & lines, int pos) {
    int ones = 0;
    // We need to make the bit position such that the LSB is on the right
    for (std::string & line : lines) {
        if (pos < line.size() && line[pos] == '1') {
            ones++;
        }
    }
    return ones;
}

/***
 * Compute the solution to part 1
 */
long partOne(std::vector<std::string>& lines) {
    auto row_stats = std::map<int, int>();
    
    for (std::string& line : lines) {
        byteCount(row_stats, line);
    }

    long gamma = 0, epsilon = 0;
    int total_rows = lines.size();

    for (const auto & stat : row_stats) {
        if (stat.second > (total_rows / 2)) {
            // We know that there is a greater number of ones if it is greater
            // than half of the list
            gamma |= (1 << stat.first); 
        } else {
            epsilon |= (1 << stat.first); 
        }
    }

    std::cout << "Gamma: " << gamma << std::endl;
    std::cout << "Epsilon: " << epsilon << std::endl;
    return  gamma * epsilon;
}

/***
 * Compute the solution to part 2
 */
long partTwo(std::vector<std::string>& lines) {
    std::vector<std::string> current_oxy_search = lines;
    std::vector<std::string> current_scrubber_search = lines;

    // Assuming each line has the same number of bits
    int max_pos = lines[0].size();
    int num_rows = lines.size();

    // For every bit position from MSB to LSB, filter out the searched values.
    for (int pos = 0; pos < max_pos && current_scrubber_search.size() > 1; pos++) {
        // First the oxy
        int oxy_frequency = countOnes(current_oxy_search, pos);
        if (oxy_frequency >= current_oxy_search.size() / 2.0) {
            // We have more or equal ones
            current_oxy_search.erase(std::remove_if(
                current_oxy_search.begin(),
                current_oxy_search.end(),
                [=](std::string line) { return line[pos] == '0'; }
            ), current_oxy_search.end());
        } else {
            // We have less ones than zeroes
            current_oxy_search.erase(std::remove_if(
                current_oxy_search.begin(),
                current_oxy_search.end(),
                [=](std::string line) { return line[pos] == '1'; }
            ), current_oxy_search.end());
        }
    }

    for (int pos = 0; pos < max_pos && current_scrubber_search.size() > 1; pos++) {
        // Now the scrubber values
        int scrub_frequency = countOnes(current_scrubber_search, pos);
        if (scrub_frequency >= current_scrubber_search.size() / 2.0) {
            current_scrubber_search.erase(std::remove_if(
                current_scrubber_search.begin(),
                current_scrubber_search.end(),
                [=](std::string line) { return line[pos] == '1'; }
            ), current_scrubber_search.end());
        } else {
            current_scrubber_search.erase(std::remove_if(
                current_scrubber_search.begin(),
                current_scrubber_search.end(),
                [=](std::string line) { return line[pos] == '0'; }
            ), current_scrubber_search.end());
        }
    }

    std::cout << current_scrubber_search.size() << std::endl;
    std::cout << current_oxy_search.size() << std::endl;
    long oxy = std::stoi(current_oxy_search[0], 0, 2);
    long scrub = std::stoi(current_scrubber_search[0], 0, 2);

    std::cout << oxy << std::endl;
    std::cout << scrub << std::endl;
    return oxy * scrub;
}

int main (int argc, char ** argv) {
    if (argc >= 2) {
        auto file_contents = readFileFromInput(std::string(argv[1]));
        std::cout << "Part 1 Final: " << partOne(file_contents) << std::endl;
        std::cout << "Part 2 Final: " << partTwo(file_contents) << std::endl;
    }
    return 0;
}