#pragma once
#include <string>
#include <fstream>
#include <iostream>

/**
 * @class FileManager
 * @brief Klasa pomocnicza do zapisu i odczytu danych z plików tekstowych.
 *
 * Udostępnia statyczne metody do:
 * - zapisywania tekstu do pliku,
 * - odczytywania tekstu z pliku.
 * Klasa nie wymaga tworzenia instancji, wszystkie funkcje są statyczne.
 */
class FileManager
{
public:
    /**
     * @brief Zapisuje dane do pliku tekstowego.
     *
     * @param filename Ścieżka do pliku, do którego zapisujemy dane
     * @param data Tekst do zapisania w pliku
     * @return true jeśli zapis powiódł się, false w przypadku błędu
     */
    static bool saveToFile(const std::string& filename, const std::string& data)
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

    /**
     * @brief Odczytuje dane z pliku tekstowego.
     *
     * @param filename Ścieżka do pliku, z którego odczytujemy dane
     * @param outData Zmienna, do której zostaną zapisane odczytane dane
     * @return true jeśli odczyt powiódł się, false w przypadku błędu
     */
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
