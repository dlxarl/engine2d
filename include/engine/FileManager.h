#pragma once
#include <string>
#include <fstream>
#include <iostream>

class FileManager
{
public:
    static bool = saveToFile(const std::string& filename, const std::string& data)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Nie można otworzyć pliku do zapisu: " << filename << std::endl;
            return false;
        }
        file << data;
        file.close();
        return true;
    }

    static bool loadFromFile(const std::string& filename, std::string& outData)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Nie można otworzyć pliku do odczytu: " << filename << std::endl;
            return false;
        }
        outData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
        return true;
    }
};
