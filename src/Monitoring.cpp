#include "Monitoring.hpp"

Monitoring::Monitoring(char *json_path) : configuration(json_path)
{ 
    UpdateInstantCpuLoad();
}

void Monitoring::UpdateInstantCpuLoad()
{
    std::vector<CPUStats> prev_cpu_stats;
    ReadCpuStats(prev_cpu_stats);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<CPUStats> current_cpu_stats;
    ReadCpuStats(current_cpu_stats);

    for (int i = 0; i < current_cpu_stats.size(); i++)
    {
        if (configuration.metrics.cpu_ids.count(i))
        {
            float instant_load = CalculateCpuLoad(prev_cpu_stats[i], current_cpu_stats[i]);

            std::cout << "Instant load: " << instant_load << "%" << std::endl;
        }
    }
}

void Monitoring::ReadCpuStats(std::vector<CPUStats>& cpu_stats)
{
    std::ifstream filestat(filestat_str);

    if (filestat.is_open())
    {
        std::string line;
        std::getline(filestat, line);
    
        while(std::getline(filestat, line))
        {
            if (line.find(cpu_substr) != std::string::npos)
            {
                std::stringstream ss(line);
                CPUStats stats{};

                std::string label;
                
                ss >> label >> stats.user >> stats.nice >> stats.system >> 
                stats.idle >> stats.iowait >> stats.irq >> stats.softirq >> stats.steal;


                cpu_stats.emplace_back(stats);
            }            
        }    
    }
    else
    {
        throw std::logic_error(proc_stat_error_msg + filestat_str);
    }
}

float Monitoring::CalculateCpuLoad(const CPUStats& prev, const CPUStats& curr)
{
    // user = 4705;
    // nice = 306;
    // system = 584;
    // idle = 3699;
    // iowait = 23;
    // irq = 23;
    // softirq = 0;
    // steal = 0;

    unsigned long prev_total = prev.user + prev.nice + 
        prev.system + prev.idle + prev.iowait + prev.irq + prev.softirq + prev.steal;

    unsigned long curr_total = curr.user + curr.nice + curr.system + curr.idle + curr.iowait + 
        curr.irq + curr.softirq + curr.steal;

    unsigned total_diff = curr_total - prev_total;

    unsigned idle_diff = (curr.iowait + curr.idle) - (prev.iowait + prev.idle);

    //std::cout << "Time: " << total_time << " " << idle_time << " " << usage_time <<std::endl;

    float load = (total_diff > 0) ? 100.0f * (total_diff - idle_diff) / total_diff : 0;

    // std::cout << "Test: " << label << " " << user << " " << nice << " " <<system 
    // << " " <<idle << " " <<iowait << " " <<irq
    // << softirq << " " << steal << std::endl;
    return roundf(load * 100) / 100;
}