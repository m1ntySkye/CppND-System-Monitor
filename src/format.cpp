#include "format.h"

#include <boost/format.hpp>
#include <map>
#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int s = seconds % 60;
  int m = ((seconds - s) / 60) % 60;
  int h = ((seconds - s - m * 60) / 60 * 60) % (60 * 60);
  return str(boost::format("%02d:%02d:%02d") % h % m % s);
}

// FileSize: parse a string describing file size into bytes
// INPUT: string matching  \s*({0-9}+)\s*({a-zA-Z}?B)\s*
// OUTPUT: Bytes
// int Format::FileSize(std::string sizeStr) {
//   std::map<std::string, int> prefix{
//       {"k", 1024},
//       {"m", 1024 * 1024},
//       {"g", 1024 * 1024 * 1024},
//       {"t", 1024 * 1024 * 1024 * 1024},
//       {"p", 1024 * 1024 * 1024 * 1024 * 1024},
//       {"y", 1024 * 1024 * 1024 * 1024 * 1024 * 1024}};
// }
