/*
| Core Component |
|----------------|
|V`trim`         |
|V`load_file`    |
| `parse_line`   |
| `parse`        |
| `get_value`    |
| `set_value`    |
| `save_to_file` |

Algorithm
1. Load file
2. Init empty data card
3. for every stroke do manipulations
4. If key doesn't exist write up
5. User can change files and get data
6. Write file

Mission is:
parse_line

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>



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

struct ParsedLine {
    LineType type;
    std::string section;
    std::string key;
    std::string value;
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

ParsedLine parse_line(const std::string& line) {
    ParsedLine parsed_line;
    LineType type_line = classify_line(line);
    std::string result = trim(line);
    //std::string class_line = to_string(type_line);

    parsed_line.type = type_line;

    switch (type_line) {
        case LineType::SECTION: {
            size_t start = result.find_first_of('[');
            size_t end = result.find_last_of(']');
            parsed_line.section = result.substr(start + 1, end - start - 1);
            break;
        }
            case LineType::KEY_VALUE: {
            //size_t start = result.find_first_of('=');
            size_t end = result.find_last_of('=');

            if (end != std::string::npos) {
                //std::string key = result.substr(start + 1, result.size() - start - 1);
                std::string key = trim(result.substr(0, end));
                std::string value = trim(result.substr(end + 1));
                parsed_line.key = key;
                parsed_line.value = value;
                break;
            }
        }
            default: {
            break;
        }
    }

    return parsed_line;
}

std::vector<std::string> load_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return {};
    }
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {

    // std::vector<std::string> test_lines = {
    //     "  [video]  ",
    //     "fullscreen = true",
    //     "resolution =  1920x1080 ",
    //     "; this is a comment",
    //     "# legacy config",
    //     "",
    //     "weird line without equals"
    // };
    //
    // for (const auto& line : test_lines) {
    //     ParsedLine parsed = parse_line(line);
    //     std::cout << "Line: \"" << line << "\"\n"
    //               << "Type: " << to_string(parsed.type) << "\n"
    //               << "Section: " << parsed.section << "\n"
    //               << "Key: " << parsed.key << "\n"
    //               << "Value: " << parsed.value << "\n"
    //               << "------------------------" << std::endl;
    // }



    // std::vector<std::string> lines = load_file("PATH");
    //
    // for (const auto& line : lines) {
    //     std::cout << "[" << line << "]" << std::endl;
    // }

    // std::string test_data = "  ;[lol = cheburek]            ";
    // std::cout << "[" << trim(test_data) << "]" << std::endl;
    // LineType line_type = classify_line(test_data);
    // std::cout << "\"" << test_data << "\" -> " << to_string(line_type) << std::endl;
    return 0;
}