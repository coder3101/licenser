#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#define CUSTOM_HEADER_NAME ".header"

namespace licenser::configmgr {
class CustomHeader {
 public:
  static std::string read(std::string dir);
  static bool exists(std::string p);
};
}  // namespace licenser::configmgr