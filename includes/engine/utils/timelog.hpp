#pragma once

#include <iostream>
#include <chrono>

#define LOG_TIME_BEFORE \
    auto start_time = std::chrono::high_resolution_clock::now();

#define LOG_TIME_AFTER \
    auto end_time = std::chrono::high_resolution_clock::now(); \
    auto time_diff = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); \
    std::cout << "Time taken: " << time_diff.count() << " microseconds" << std::endl;