# INI Parser

A lightweight C++ command-line tool for parsing and modifying `.ini` configuration files.

## Features

- Parses INI files into a nested `std::map`
- Supports `[section]`, `key = value` pairs
- Allows retrieving and setting values via console
- Saves modified configuration back to a file

## Use Case

Targeted at developers who want a simple and readable INI parsing mechanism for small-scale config-driven C++ tools.

## How It Works

### 1. Load `.ini` File

The tool reads the file line-by-line and classifies content as:

- Sections (`[General]`)
- Key-value pairs (`name = value`)
- Comments (`;` or `#`)
- Empty or unknown lines (ignored)

### 2. Interact via CLI

After loading, the program allows the user to:

- Retrieve a value from a specific section
- Modify a value or create new section/key
- Save the changes to a new file

## Example

```
[General]
UseChatGPT = true

[Network]
Port = 8080
```

```
Welcome to ini parser!
Please enter the path to ini file: ./config.ini
File is loaded and parsed, please enter what you are want to do:
1 - Get value 
2 - Set value 
3 - Save changes to file
e - Exit
```

## Code Structure

| Component | Description |
| --- | --- |
| `trim` | Trims leading/trailing whitespace |
| `load_file` | Loads file into memory |
| `parse_line` | Parses a line into structured data |
| `parse` | Builds the config `map` |
| `get_value` | Retrieves a value from the config |
| `set_value` | Updates or adds a value |
| `save_to_file` | Saves config back to file |

## Limitations

- No support for multi-line values
- Comments are not preserved in output
- No input validation for malformed `.ini` files

## Build Instructions

Use any standard C++17-compatible compiler:

```bash
g++ -std=c++17 -o ini-parser main.cpp
./ini-parser
```

> Tested on Linux and Windows (g++ / MSVC).

## License

MIT — feel free to use and modify.