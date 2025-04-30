cmake_minimum_required(VERSION 3.10)
project(CdtlTestTask)

include_directories(include)
include_directories(include/utils)

add_executable(monitoring main.cpp src/Configuration.cpp src/Metrics.cpp src/Monitoring.cpp)


