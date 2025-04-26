#pragma once

#include <iostream>
#include <fstream>

#include "Metrics.hpp"

class Configuration 
{
//vars
public:
    int period;

    Metrics metrics;

    //outputs
    bool console;
    bool log;
    std::string log_path; 

private:

//methods
public:
    Configuration();
    Configuration(std::string json_path);
    Configuration(const json &json);
    Configuration(char* json_path);

private:
    void init(const json &json);
    void ParseSettings(const json &json);
    void ParseOutputs(const json &json);
    void ParseLog(const json &json);
};