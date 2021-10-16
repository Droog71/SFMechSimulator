#include <file_handler.h>
#include <iostream>
#include <fstream>

// Reads the contents of a file line by line and returns the result
std::string get_file_contents(std::string file_path)
{
    std::ifstream stream;
    stream.open(file_path);
    std::string text;
    std::string result;
    while(getline(stream, text))
    {
        result += text + "\n";
    }
	return result;
}

// Writes the given data to a file, overwriting the existing data
std::string write_to_file(std::string file_path, std::string data)
{
    std::ofstream file;
    file.open(file_path);
    file << data << "\n";
    file.close();
    return data;
}

// Gets the contents of a file, adds the given data and overwrites the file
std::string append_file(std::string file_path, std::string data)
{
    std::string current = get_file_contents(file_path);
    std::string appended = current + data;
    return write_to_file(file_path, appended);
}
