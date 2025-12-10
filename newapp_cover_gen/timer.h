#include <iostream>
#include <chrono>
#include <string>
#include <map>

class Timer {
public:
    // 记录整个程序的开始时间
    static void startGlobalTimer() {
        globalStart = std::chrono::high_resolution_clock::now();
    }

    // 计算并打印总耗时
    static void stopGlobalTimer() {
        auto globalEnd = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(globalEnd - globalStart).count();
        std::cout << "\n[Total Execution Time] " << duration << " μs (" 
                  << duration / 1000.0 << " ms)\n";
    }

    // 构造函数：进入作用域即开始计时
    explicit Timer(const std::string& functionName, bool autoPrint = true)
        : funcName(functionName), print(autoPrint), start(std::chrono::high_resolution_clock::now()) {}

    // 析构函数：自动计算并输出时间
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        totalTime[funcName] += duration;  // 记录函数总耗时

        if (print) {
            std::cout << "[Timer] " << funcName << " executed in " << duration << " μs ("
                      << duration / 1000.0 << " ms)\n";
        }
    }

    // 统计所有函数的执行时间
    static void report() {
        std::cout << "\n[Timer Report] Function Execution Summary:\n";
        for (const auto& entry : totalTime) {
            std::cout << "  " << entry.first << ": " << entry.second << " μs ("
                      << entry.second / 1000.0 << " ms)\n";
        }
    }

private:
    std::string funcName;
    bool print;
    std::chrono::high_resolution_clock::time_point start;
    static std::map<std::string, long long> totalTime;  // 记录每个函数的总耗时
    static std::chrono::high_resolution_clock::time_point globalStart;  // 记录全局起始时间
};

class HandTimer {
public:
    // 开始计时
    void start(const std::string& function_name) {
        start_times[function_name] = std::chrono::high_resolution_clock::now();
    }

    // 结束计时，并记录耗时
    void stop(const std::string& function_name) {
        auto end_time = std::chrono::high_resolution_clock::now();
        if (start_times.find(function_name) != start_times.end()) {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_times[function_name]).count();
            function_durations[function_name] += duration;
            total_duration += duration;
        } else {
            std::cerr << "Error: Timer for " << function_name << " was not started!" << std::endl;
        }
    }

    // 显示所有函数的耗时
    void report() const {
        std::cout << "Function Execution Time Report:\n";
        for (const auto& entry : function_durations) {
            std::cout << "  " << entry.first << ": " << entry.second << " µs" << std::endl;
        }
        std::cout << "Total execution time: " << total_duration << " µs" << std::endl;
    }

private:
    std::map<std::string, std::chrono::high_resolution_clock::time_point> start_times;
    std::map<std::string, long long> function_durations;
    long long total_duration = 0;
};