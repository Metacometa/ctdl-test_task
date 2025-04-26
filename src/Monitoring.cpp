#include "Monitoring.hpp"

Monitoring::Monitoring(char *json_path) : configuration(json_path)
{
    std::ifstream filestat(filestat_str);
    if (filestat.is_open())
    {
        GetCpuLoad(filestat, 1);
    }
    else
    {
        throw std::logic_error(proc_stat_error_msg + filestat_str);
    }
}

std::string Monitoring::GetCpuLoad(std::ifstream& file, const int& id)
{
    std::string line;
    std::getline(file, line);

    for (int i = 0; i <= id; ++i)
    {
        std::getline(file, line);
    } 

    std::cout << line << std::endl;

    std::stringstream ss;
    ss << line;

    std::string answ = "";
    ss >> answ;

    std::cout << line << std::endl;
    std::cout << answ << std::endl;

    std::cout << std::endl;
    return line;
}