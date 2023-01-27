#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <filesystem>

namespace LinuxParser {
// /proc/ Paths
const std::filesystem::path kProcDirectory{"/proc/"};
const std::filesystem::path kCmdlineFilename{"cmdline"};
const std::filesystem::path kCpuinfoFilename{"cpuinfo"};
const std::filesystem::path kStatusFilename{"status"};
const std::filesystem::path kStatFilename{"stat"};
const std::filesystem::path kUptimeFilename{"uptime"};
const std::filesystem::path kMeminfoFilename{"meminfo"};
const std::filesystem::path kVersionFilename{"version"};
const std::filesystem::path kSchedstatFilename{"schedstat"};

// /etc/ Paths
const std::filesystem::path kEtcDirectory{"/etc/"};
const std::filesystem::path kOSPath{"os-release"};
const std::filesystem::path kPasswordPath{"passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);

// Helpers:

// read a line from a file which matches the key.
// returns empty string if file or line starting with key not found.
std::string readKeyedFile(std::filesystem::path file, std::string key);

// read and return the full contents of a file
std::string readFile(std::filesystem::path file);

};  // namespace LinuxParser

#endif // SYSTEM_PARSER_H
