#include "Monitoring.hpp"

void print(const int arr[], const int& size);
void test_print_proc();

int main(int argc, char* argv[])
{
    // test_print_proc();
    // return 0;
    if (argc > 1)
    {
        try
        {
            Monitoring monitoring(argv[1]);
            // std::cout << "Period: " << configuration.period << std::endl;
            
            // std::cout << "Ids: ";
            // for(auto &i: configuration.metrics.cpu_ids)
            // {
            //     std::cout << i << ", ";
            // }
            // std::cout << std::endl;
    
            // std::cout << "Used memory: " << configuration.metrics.used_memory;
            // std::cout << "/Free memory: " << configuration.metrics.free_memory << std::endl;
    
            // std::cout << "Console: " << configuration.console << std::endl;
            // std::cout << "Log: " << configuration.log << " " << configuration.log_path << std::endl;
        }
        catch (json::parse_error error)
        {
            std::cout << "Failed to parse json file" << std::endl;
        }
        catch (json::type_error error)
        {
            std::cout << "Incorrect values in json" << std::endl;
        }
        catch (std::logic_error error)
        {
            std::cout << error.what() << std::endl;
        }
    }
    else
    {
        std::cout << "No arguments" << std::endl;
    }



    // std::fstream json_file("data.json");
    // json json = json::parse(json_file);

    // if (json["lol"][3] != nullptr)
    // {
    //     std::cout << json["lol"][3] << std::endl;
        

    //     std::cout << json["lol"].is_array() << std::endl;
    //     int arr = json["lol"][0];

    //     std::cout << arr << std::endl;
    //     //print(json["lol"]);
    // }

    return 0;
}

void print(const int arr[], const int& size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl;
}

void test_print_proc()
{
    std::ifstream filestat("/proc/stat");

    std::string line;
    std::getline(filestat, line);
    
    unsigned n;
    while(std::getline(filestat, line))
    {
        // use n here...
        std::cout << line << '\n';
    }
}
