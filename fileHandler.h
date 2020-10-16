#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<uint32_t > readFromFile(const char* filePath)
{
    std::vector<uint32_t > numbers;
    std::cout << "read file: " << filePath << "..." << std::endl;
    std::ifstream in(filePath);
    if (in.is_open())
    {
        std::string line;
        std::getline(in, line);
        int count = std::stoi(line);

        std::cout << "total: " << count << " elems" << std::endl;

        int idx = 0;
        while (in.good() && idx < count) {
            std::getline(in, line);
            //long val = std::stol(line);
            //std::cout << "as long: " << val << std::endl;
            unsigned long ulval = std::stoul(line);
            //std::cout << "as unsigned long: " << ulval << std::endl;
            numbers.push_back((uint32_t)ulval); // auto cast to uint
            idx++;
        }
    }
    else std::cout << "Error opening " << filePath << std::endl;

    if (!in.eof() && in.fail())
        std::cout << "error reading " << filePath << std::endl;

    in.close();
    return numbers;
}