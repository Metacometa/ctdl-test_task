#include "Monitoring.hpp"

Monitoring::Monitoring(char *json_path) : config(json_path)
{ 
    while(true)
    {
        UpdateInstantCpuLoad();
        UpdateMemInfo();

        if (config.console)
        {
            Output(std::cout);
        }

        if (config.log)
        {
            std::ofstream file(config.log_path, std::ios::app);

            if (file.is_open())
            {
                Output(file);
            }
            else
            {
                throw my_parse_error(incorrect_logfile_error_msg);
            }

            file.close();
        }

        std::this_thread::sleep_for(std::chrono::seconds(config.period));
    }
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
        if (config.metrics.cpu_ids.count(i))
        {
            float instant_cpu_load = CalculateInstantCpuLoads(prev_cpu_stats[i], current_cpu_stats[i]);

            instant_cpu_loads[i] = instant_cpu_load;
        }
    }

    for(auto& cpu_id:config.metrics.cpu_ids)
    {
        if (!instant_cpu_loads.count(cpu_id))
        {
            throw my_parse_error(nonexistent_kernel_error_msg + std::to_string(cpu_id));
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
        throw my_parse_error(proc_stat_error_msg + filestat_str);
    }

    filestat.close();
}

float Monitoring::CalculateInstantCpuLoads(const CPUStats& prev, const CPUStats& curr)
{
    unsigned long prev_total = prev.user + prev.nice + 
        prev.system + prev.idle + prev.iowait + prev.irq + prev.softirq + prev.steal;

    unsigned long curr_total = curr.user + curr.nice + curr.system + curr.idle + curr.iowait + 
        curr.irq + curr.softirq + curr.steal;

    unsigned total_diff = curr_total - prev_total;

    unsigned idle_diff = (curr.iowait + curr.idle) - (prev.iowait + prev.idle);

    float load = (total_diff > 0) ? 100.0f * (total_diff - idle_diff) / total_diff : 0;

    return roundf(load * 100) / 100;
}

void Monitoring::UpdateMemInfo()
{
    std::string mem_line;
    std::string label;
    unsigned long total_memory, temp_used_memory, temp_free_memory;

    std::ifstream meminfo(file_meminfo_str);
    std::stringstream ss;

    if (meminfo.is_open())
    {
        std::getline(meminfo, mem_line);
        ss << mem_line;
        ss >> label >> total_memory;

        std::getline(meminfo, mem_line);

        std::getline(meminfo, mem_line);
        ss << mem_line;
        ss >> label >> temp_free_memory;

        temp_used_memory = total_memory - temp_free_memory;

        used_memory = temp_used_memory / 1024;
        free_memory = temp_free_memory / 1024;
    }
    else
    {
        throw my_parse_error(meminfo_error_msg + file_meminfo_str);
    }    

    meminfo.close();
}

void Monitoring::Output(std::ostream& stream)
{
    int padding = 12;

    std::time_t t = std::time(nullptr);
    std::tm now{};

    localtime_r(&t, &now);

    std::stringstream ss;
    ss << std::put_time(&now, "%H:%M:%S");

    std::string time;
    ss >> time;

    stream << std::left << std::setw(padding) << time;

    for(auto& cpu_id:config.metrics.cpu_ids)
    {
        if (instant_cpu_loads.count(cpu_id))
        {
            stream << std::left << std::setw(padding) << ("core " + std::to_string(cpu_id));
        }   
    }
    stream << std::endl;
    stream << std::left << std::setw(padding) << "CPU";

    for(auto& cpu_id:config.metrics.cpu_ids)
    {
        if (instant_cpu_loads.count(cpu_id))
        {
            std::stringstream s;
            s << instant_cpu_loads[cpu_id] << "%";

            stream << std::left << std::setw(padding) << s.str();
        }   
    }

    stream << std::endl << std::endl;

    stream << std::left << std::setw(padding) << time 
        << std::left << std::setw(padding) << "Used"
        << std::left << std::setw(padding) << "Free";

    stream << std::endl;

    stream << std::left << std::setw(padding) << "Memory"
        << std::left << std::setw(padding) << (std::to_string(used_memory) + " MB")
        << std::left << std::setw(padding) << (std::to_string(free_memory) + " MB");


    stream << std::endl << std::endl;
}