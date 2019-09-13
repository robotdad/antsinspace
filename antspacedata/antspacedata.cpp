#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <ctime>
#include <sys/time.h>

unsigned long int argcheck(std::string arg)
{
    try
    {
        std::size_t pos;
        unsigned long int x = std::stoi(arg, &pos);
        if (pos < arg.size())
        {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
        return x;
    }
    catch (std::invalid_argument const &ex)
    {
        std::cerr << "Invalid number: " << arg << '\n';
    }
    catch (std::out_of_range const &ex)
    {
        std::cerr << "Number out of range: " << arg << '\n';
    }
}

std::string currentTime(){
    char            fmt[64], buf[64];
    struct timeval  tv;
    struct tm       *tm;

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    strftime(fmt, sizeof fmt, "%Y-%m-%d-%H-%M-%S.%%06u", tm);
    snprintf(buf, sizeof buf, fmt, tv.tv_usec);
    return buf;
}

int main(int argc, char *argv[])
{ 
    if (argc < 4)
    {
        return 1;
    }

    int numfiles = argcheck(argv[1]);
    unsigned long int minLines = argcheck(argv[2]);
    unsigned long int maxLines = argcheck(argv[3]);

    auto pstart = std::chrono::system_clock::now();
    std::cout << "Writing " << numfiles << " csv files with at least " << minLines << " and no more than "
              << maxLines << " lines." << std::endl;

    //setup for random number generator for number of lines
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> rndLines(minLines, maxLines);

    //array for random machine in output file
    const std::string machines[10] = {"Formica", "Odontomachus", "Ecitoninae",
                                      "Leptomyrmex", "Lasius", "Linepithema",
                                      "Myrmecocystus", "Pheidole", "Atta", "Myrmica"};
    std::uniform_int_distribution<> rndMachine(0, 9);

    //array for random type in output file
    const std::string screwType[4] = {"Socket", "Hex", "Thumb", "Round"};
    std::uniform_int_distribution<> rndScrewType(0, 3);

    std::ofstream ofile;

    for (size_t i = 0; i < numfiles; i++)
    {
        auto start = std::chrono::system_clock::now();
        int lines = rndLines(eng);
        std::string currenttime = currentTime();
        std::string machine = machines[rndMachine(eng)];
        std::string fname = machine + "_" + currenttime + ".csv";

        std::cout << "Starting file " << fname << std::endl;
        ofile.open(fname);
        ofile << "Time,Type" <<std::endl;
        for (size_t i = 0; i < lines; i++)
        {
            ofile << currentTime() << ",";
            ofile << screwType[rndScrewType(eng)] << std::endl;
        }

        ofile.close();

        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Wrote " << fname << " in " << elapsed_seconds.count() << " at " << std::ctime(&end_time);
    }

    auto pend = std::chrono::system_clock::now();
    std::time_t pend_time = std::chrono::system_clock::to_time_t(pend);
    std::chrono::duration<double> elapsed_seconds = pend - pstart;
    std::cout << "Wrote " << numfiles << " files in " << elapsed_seconds.count() << " at " << std::ctime(&pend_time);
    return 0;
}