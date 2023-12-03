#include "util.h"

std::vector<std::string> aoc_util::readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        //std::cout << "Reading in file: " << filename << std::endl;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    //std::cout << "Read in " << lines.size() << " lines." << std::endl;
    return lines;
}

std::string aoc_util::readFileToSingleLine(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string line, result;

    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }

    while (getline(file, line)) {
        buffer << line;
    }

    result = buffer.str();
    file.close();
    return result;
}


std::vector<std::string> aoc_util::splitString(const std::string& input, const std::string& regex) {
    const std::regex reg(regex); 
    std::sregex_token_iterator iter(input.begin(), input.end(), reg, -1);
    const std::sregex_token_iterator end;

    std::vector<std::string> result;
    while (iter != end) {
        result.push_back(*iter++);
    }
    return result;
}
