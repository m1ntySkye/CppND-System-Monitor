#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kEtcDirectory/kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory/kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float utilization = -1.0;
  string line, key, unit;
  int MemTotal = -1.0;
  int MemFree = -1.0;
  int value = 0;
  const string KeyMemTotal("MemTotal:");
  const string KeyMemFree("MemFree:");
  // file to parse: /proc/meminfo (LinuxParser::kMeminfoFilename)
  std::ifstream stream(kProcDirectory/kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream(line) >> key >> value;// >> unit;
      if (key == KeyMemTotal) {
        MemTotal = value;
      } else if (key == KeyMemFree) {
        MemFree = value;
      }
    }
    if (MemTotal > 0 && MemFree > 0) {
      utilization = ((float)(MemTotal - MemFree) / MemTotal);
    } else {
      throw "parsing meminfo failed";
    }
  }
  return utilization;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream stream(kProcDirectory/kUptimeFilename);
  if (stream.is_open()) {
    long uptime = -1.0;
    long idleTime = -1.0;
    stream >> uptime >> idleTime;
    return uptime;
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{ 
  readKeyedFile(kProcDirectory/kSchedstatFilename,"timestamp");
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  std::istringstream totalLine(readKeyedFile(kProcDirectory/kStatFilename,"processes"));
  int nprocs = -1;
  totalLine >> nprocs;
  return nprocs;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  std::istringstream runningLine(readKeyedFile(kProcDirectory/kStatFilename,"procs_running"));
  int runningProcs = -1;
  runningLine >> runningProcs;
  return runningProcs;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) {
  std::string pidFile = readFile(kProcDirectory/std::filesystem::path(to_string(pid))/kStatFilename);
  pidFile.
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]])
{
  return readFile(kProcDirectory/std::filesystem::path(to_string(pid))/kCmdlineFilename);
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return "LinuxParser::Ram test string"; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return "LinuxParser::Uid test string"; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return "LinuxParser::User test string"; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }


std::string LinuxParser::readKeyedFile(std::filesystem::path file, std::string key){
  string line{}, lineKey{};
  std::ifstream stream(file);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> lineKey;
      if(key == lineKey){
        //get remaining line from buffer;
        std::getline(linestream,line);
        break;
      }
    }
  }
  return line;
}

std::string LinuxParser::readFile(std::filesystem::path file, std::string key){
  string file_s = "";
  std::ifstream stream(file);
  if (stream.is_open()) {
    std::stringstream sstream;
    sstream << stream.rdbuf();
    file_s = sstream.str();
  }
  return file_s;
}
