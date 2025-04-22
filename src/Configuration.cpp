#include "Configuration.hpp"

Configuration::Configuration()
{
    console = false;
    log = false;
    log_path = "";
}

Configuration::Configuration(std::string json_path) : Configuration()
{
    std::fstream json_file(json_path);
    json json = json::parse(json_file);

    init(json);
}

Configuration::Configuration(const json &json) : Configuration()
{
    init(json);
}

Configuration::Configuration(char* json_path) : Configuration()
{
    std::fstream json_file(json_path);
    json json = json::parse(json_file);

    init(json);
}

void Configuration::init(const json &json)
{
    ParseSettings(json);

    metrics.init(json);

    ParseOutputs(json);
}

void Configuration::ParseSettings(const json &json)
{
    if (!json.contains(settings_str))
    {
        throw std::logic_error(settings_error_msg); 
    }

    auto json_settings = json[settings_str];

    if (!json_settings.contains(period_str))
    {
        throw std::logic_error(period_error_msg);
    }

    std::string string_period = json_settings[period_str].get<std::string>();
    period = std::stoi(string_period);
}

void Configuration::ParseOutputs(const json &json)
{
    if (!json.contains(outputs_str))
    {
        throw std::logic_error(outputs_error_msg);
    }

    auto outputs = json[outputs_str];

    for(auto& output:outputs)
    {
        if (!output.contains(type_str))
        {
            throw std::logic_error(type_error_msg);
        }

        std::string type = output[type_str].get<std::string>();
        if (type == console_str)
        {
            console = true;
        }
        else if (type == log_str)
        {
            ParseLog(output);
        }
        else
        {
            throw std::logic_error(metrics_uknown_type_error_msg + type);
        }
    }
}

void Configuration::ParseLog(const json &json)
{
    if (!json.contains(path_str))
    {
        throw std::logic_error(path_error_msg);
    }

    if (!json[path_str].is_string())
    {
        throw std::logic_error(path_string_error_msg);      
    }

    log = true;
    log_path = json[path_str].get<std::string>();
}