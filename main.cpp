/*
| Core Component |
|----------------|
|V`trim`         |
|V`load_file`    |
|V`parse_line`   |
|V`parse`        |
|V`get_value`    |
|V`set_value`    |
|V`save_to_file` |

| etc Component  |
| get_keys       |
| get_section    |
| get_values     |

Algorithm
1. Load file
2. Init empty data card
3. for every stroke do manipulations
4. If key doesn't exist write up
5. User can change files and get data
6. Write file

Mission is:
get_values

*/

#include <iostream>
#include <fstream>
#include <map>
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

    parsed_line.type = type_line;

    switch (type_line) {
        case LineType::SECTION: {
            size_t start = result.find_first_of('[');
            size_t end = result.find_last_of(']');
            parsed_line.section = result.substr(start + 1, end - start - 1);
            break;
        }
            case LineType::KEY_VALUE: {
            size_t end = result.find_last_of('=');

            if (end != std::string::npos) {
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

std::map<std::string, std::map<std::string, std::string>> parse(const std::vector<std::string>& lines) {
    std::map<std::string, std::map<std::string, std::string>> config;

    std::string current_section;


    for (const auto& line : lines) {
        ParsedLine parsed_line = parse_line(line);
        if (parsed_line.type == LineType::SECTION) {
            current_section = parsed_line.section;
        }
        else if (parsed_line.type == LineType::KEY_VALUE) {
            config[current_section][parsed_line.key] = parsed_line.value;
        }
    }

    return config;
}

std::string get_value(std::map<std::string,
    std::map<std::string, std::string>>& config,
    const std::string& key,
    const std::string& section = "General",
    const std::string& value = "") {

    std::string result;

    if (config.find(section) != config.end()) {
        if (config[section].find(key) != config[section].end()) {
            result = config[section][key];
        } else result = "Key not found";
    } else result = "Section not found";

    return result;

}

std::string set_value(std::map<std::string,
    std::map<std::string,
    std::string>>& config,
    const std::string& key,
    const std::string& user_value,
    const std::string& section = "General") {
    // std::string get_line = get_value(config, key, section);

    bool new_section = config.find(section) == config.end();
    bool new_key = false;

    if (!new_section) {
        new_key = config[section].find(key) == config[section].end();
    }

    std::string result = config[section][key] = user_value;

    if (new_section) std::cout << "Created new section - " << section << " and new key - " << key << std::endl;
    else if (new_key) std::cout << "Created new key: " << key << std::endl;
    else std::cout << "Updated existing value: " << user_value << std::endl;

    return result;

}

void save_to_file(std::map<std::string,
    std::map<std::string,
    std::string>>& config,
    const std::string& filename) {

    std::ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return;
    }

    for (const auto& [section, pairs] : config   ) {
        file << "[" << section << "]" << "\n";
        for (const auto& [key, value] : pairs) {
            file << key << " = " << value << std::endl;
        }

        file << std::endl;
    }

    file.close();

}

int main() {

    std::cout << "Welcome to ini parser!" << std::endl;
    std::cout << "Please enter the path to ini file: ";

    std::string file_path;
    std::getline(std::cin, file_path);
    std::map<std::string, std::map<std::string, std::string>> config = parse(load_file(file_path));

    std::cout << "File is loaded and parsed, please enter what you are want to do: " << std::endl;

    while (true) {

        std::cout << "1 - Get value \n2 - Set value \n3 - Save changes to file\ne - Exit " << std::endl;

        std::string user_choice;
        std::getline(std::cin, user_choice);

        switch (user_choice[0]) {
            case '1': {
                std::string section, key;
                std::cout << "Please enter the section" << std::endl;
                std::getline(std::cin, section);
                std::cout << "Please enter key" << std::endl;
                std::getline(std::cin, key);

                std::string value = get_value(config, key, section);
                std::cout << key << " = " << value << std::endl;
                break;
            }
            case '2': {
                std::string section, key, value;
                std::cout << "Please enter the section" << std::endl;
                std::getline(std::cin, section);
                std::cout << "Please enter the key" << std::endl;
                std::getline(std::cin, key);
                std::cout << "Please enter new value" << std::endl;
                std::getline(std::cin, value);

                set_value(config, key, value, section);
                break;
            }
            case '3': {
                std::cout << "Please enter new file name: ";
                std::string filename;
                std::getline(std::cin, filename);

                save_to_file(config, filename);
                break;
            }
            case 'e': {
                return 0;
            }
            default: std::cerr << "Invalid input" << std::endl;
        }
    }

    return 0;
}