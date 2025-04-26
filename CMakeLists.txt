cmake_minimum_required(VERSION 3.10)
project(CdtlTestTask)

include_directories(include)

add_executable(test_task main.cpp src/Configuration.cpp src/Metrics.cpp src/Monitoring.cpp)


