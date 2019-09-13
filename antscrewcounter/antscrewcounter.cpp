#include <iostream>
#include <iterator>
#include <chrono>
#include <iomanip>
#include <locale>
#include <sstream>
#include <cstddef>

#include "csvmonkey.hpp"
using namespace csvmonkey;

static void errmsg(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

template <class T>
std::string FormatWithCommas(T value)
{
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

std::string findAntName(const std::string &str)
{

    std::size_t found = str.find_last_of("/\\");
    std::string fname = str.substr(found + 1);
    std::size_t pos = fname.find("_");
    return fname.substr(0, pos);
}

std::string findDate(const std::string &str)
{

    std::size_t found = str.find_last_of("/\\");
    std::string fname = str.substr(found + 1);
    std::size_t pos = fname.find("_");
    return fname.substr(pos+1, 10);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    const char *path = argv[1];

    MappedFileCursor cursor;
    if (!cursor.open(path))
    {
        // csvmonkey returns 0 for empty files.
        std::cout << "File " << argv[1] << " is empty" << std::endl;
        return 1;
    }

    CsvReader reader(cursor);
    CsvCursor &row = reader.row();
    if (!reader.read_row())
    {
        errmsg("Cannot read header row");
    }

    CsvCell *cellType;
    if (!row.by_value("Type", cellType))
    {
        errmsg("Cannot find Type column");
    }

    auto now = [&] { return std::chrono::high_resolution_clock::now(); };
    double total = 0.0;
    auto start = now();

    unsigned long int totalRows = 0;
    unsigned long int totalSocket = 0;
    unsigned long int totalHex = 0;
    unsigned long int totalThumb = 0;
    unsigned long int totalRound = 0;

    while (reader.read_row())
    {
        totalRows++;
        if (cellType->equals("Socket"))
        {
            totalSocket++;
        }
        else if (cellType->equals("Hex"))
        {
            totalHex++;
        }
        else if (cellType->equals("Thumb"))
        {
            totalThumb++;
        }
        else if (cellType->equals("Round"))
        {
            totalRound++;
        }
    }

    auto finish = now();
    auto usec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    struct stat st;
    stat(path, &st);

    std::cout << "File " << path << " had " << FormatWithCommas<int>(totalRows) << " rows." << std::endl;
    std::cout << "Processed in " << FormatWithCommas<int>(usec) << " us" << std::endl;
    std::cout << "Ant " << findAntName(path) << " on " << findDate(path) << std::endl;
    std::cout << "Socket screws count: " << FormatWithCommas<int>(totalSocket) << std::endl;
    std::cout << "Hex screws count: " << FormatWithCommas<int>(totalHex) << std::endl;
    std::cout << "Thumb screws count: " << FormatWithCommas<int>(totalThumb) << std::endl;
    std::cout << "Round screws count: " << FormatWithCommas<int>(totalRound) << std::endl;

    return 0;
}