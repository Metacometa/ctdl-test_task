#pragma once

#include <unordered_set>
#include <iostream>

#include "json.hpp"

#include "Utils_string.hpp"

using json = nlohmann::json;
using json_ref = nlohmann::json_abi_v3_12_0::json;

class Metrics
{
//vars
public:
    std::unordered_set<int> cpu_ids;
    bool used_memory;
    bool free_memory;

private:

//methods 
public:
    Metrics();
    void init(const json &json);

private:
    void ParseCpu(const json &json);
    void ParseMemory(const json &json);
};