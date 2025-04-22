#include "Metrics.hpp"

Metrics::Metrics()
{
    used_memory = false;
    free_memory = false;
}

void Metrics::init(const json &json)
{
    if (!json.contains(metrics_str))
    {
        throw std::logic_error(metrics_init_error_msg);
    }

    auto metrics = json[metrics_str];

    for(auto& metric:metrics)
    {
        if (!metric.contains(type_str))
        {
            throw std::logic_error(type_error_msg);
        }

        std::string type = metric[type_str].get<std::string>();
        if (type == cpu_str)
        {
            ParseCpu(metric);
        }
        else if (type == memory_str)
        {
            ParseMemory(metric);
        }
        else
        {
            throw std::logic_error(metrics_uknown_type_error_msg + type);
        }

    }
}

void Metrics::ParseCpu(const json &json)
{
    if (!json.contains(cpu_ids_str))
    {
        throw std::logic_error(cpu_ids_error_msg);
    }

    if (!json[cpu_ids_str].is_array())
    {
        throw std::logic_error(cpu_ids_array_error_msg);
    }

    for(auto& json_id:json[cpu_ids_str])
    {
        if (!json_id.is_number())
        {
            throw std::logic_error(cpu_ids_number_error_msg);      
        }
        else
        {
            cpu_ids.emplace_back(json_id.get<int>());
        }
    }
}

void Metrics::ParseMemory(const json &json)
{
    if (!json.contains(spec_str))
    {
        throw std::logic_error(spec_error_msg);
    }

    if (!json[spec_str].is_array())
    {
        throw std::logic_error(spec_array_error_msg);
    }

    for(auto& json_spec:json[spec_str])
    {
        if (!json_spec.is_string())
        {
            throw std::logic_error(spec_string_error_msg);      
        }

        std::string json_spec_str = json_spec.get<std::string>();
        if (json_spec_str == used_str)
        {
            used_memory = true;
        }
        else if (json_spec_str == free_str)
        {
            free_memory = true;
        }
        else
        {
            throw std::logic_error(unknown_spec_error_msg + json_spec_str);    
        }
    }
}