// Logger.cpp
#include "Logger.h"
#include <iostream>
#include <ctime>

namespace Motor3D {
namespace Core {
std::ofstream Logger::logFile;
std::mutex Logger::logMutex;

void Logger::Init(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    logFile.open(filename, std::ios::out | std::ios::trunc);
}

void Logger::Shutdown() {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) logFile.close();
}

static std::string Timestamp() {
    std::time_t t = std::time(nullptr);
    char buf[32];
    struct tm timeinfo;
    localtime_s(&timeinfo, &t);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return buf;
}

void Logger::Info(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) logFile << "[INFO] " << Timestamp() << ": " << msg << std::endl;
}
void Logger::Warn(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) logFile << "[WARN] " << Timestamp() << ": " << msg << std::endl;
}
void Logger::Error(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) logFile << "[ERROR] " << Timestamp() << ": " << msg << std::endl;
}
}}
