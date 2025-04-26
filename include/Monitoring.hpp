#include <sstream>

#include "Configuration.hpp"

class Monitoring
{
    Configuration configuration;

public:
    Monitoring() = delete;
    Monitoring(char *json_path);

private:
    std::string GetCpuLoad(std::ifstream& file, const int& id);
};