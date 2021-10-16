#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <sstream>

std::string get_file_contents(std::string file_path);
std::string write_to_file(std::string file_path, std::string data);
std::string append_file(std::string file_path, std::string data);

#endif
