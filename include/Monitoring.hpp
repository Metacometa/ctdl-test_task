#include <sstream>
#include <unordered_map>

#include <chrono>
#include <thread>
#include <cmath>

#include "Configuration.hpp"
#include "CPUStats.hpp"

class Monitoring
{
    Configuration configuration;

public:
    Monitoring() = delete;
    Monitoring(char *json_path);

    std::unordered_map<int, int> instant_cpu_load;

private:
    void ReadCpuStats(std::vector<CPUStats>& cpu_stats);
    void UpdateInstantCpuLoad();

    float CalculateCpuLoad(const CPUStats& prev, const CPUStats& curr);
};