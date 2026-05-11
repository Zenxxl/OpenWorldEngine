// Logger.h
#pragma once
#include <string>
#include <fstream>
#include <mutex>

namespace Motor3D {
namespace Core {
class Logger {
public:
    static void Init(const std::string& filename = "motor3d.log");
    static void Shutdown();
    static void Info(const std::string& msg);
    static void Warn(const std::string& msg);
    static void Error(const std::string& msg);
private:
    static std::ofstream logFile;
    static std::mutex logMutex;
};
}}
