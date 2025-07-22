/*
Core components
load_file
parse_line
trim
parse
get_value
set_value
save_to_file

Algorithm
1. Load file
2. Init empty data card
3. for every stroke do manipulations
4. If key doesn't exist write up
5. User can change files and get data
6. Write file

First mission is:
trim

*/

#include <iostream>
#include <fstream>
#include <string>



std::string trim(const std::string& stroke) {
    //Delete spaces between edges
    size_t start = stroke.find_first_not_of(' ');
    size_t end = stroke.find_last_not_of(' ');

    if (start == std::string::npos) {
        //stroke.clear();
        return "";
    }

    return stroke.substr(start,end - start + 1);
}

enum class LineType {
    SECTION,
    KEY_VALUE,
    COMMENT,
    EMPTY,
    UNKNOWN
};

LineType classify_line(const std::string& line) {
    std::string trimmed_line = trim(line);

    if (trimmed_line.empty()) return LineType::EMPTY;
    else if (trimmed_line[0] == '[') return LineType::SECTION;
    else if (trimmed_line[0] == ';' || trimmed_line[0] == '#') return LineType::COMMENT;
    else if (trimmed_line.find('=') != std::string::npos) return LineType::KEY_VALUE;
    else return LineType::UNKNOWN;
}

std::string to_string(LineType type) {
    switch (type) {
        case LineType::SECTION: return "SECTION";
            case LineType::KEY_VALUE: return "KEY_VALUE";
            case LineType::COMMENT: return "COMMENT";
            case LineType::EMPTY: return "EMPTY";
            default: return "UNKNOWN";
    }
}

int main() {

    // std::string test_data = "  ;[lol = cheburek]            ";
    // std::cout << "[" << trim(test_data) << "]" << std::endl;
    // LineType line_type = classify_line(test_data);
    // std::cout << "\"" << test_data << "\" -> " << to_string(line_type) << std::endl;
    return 0;
}