#include "ConfigCustomHeader.hpp"

namespace licenser::configmgr {

std::string CustomHeader::read(std::string dir) {
  std::string ans;
  if (CustomHeader::exists(dir)) {
    auto pt = std::filesystem::path(dir).append(CUSTOM_HEADER_NAME).string();
    std::ifstream stream(pt);
    if (stream.good()) {
      std::string line;
      while (std::getline(stream, line)) {
        ans += line;
        ans += '\n';
      }
    }
    stream.close();
  }
  return ans;
}

bool CustomHeader::exists(std::string p) {
  auto path = std::filesystem::path(p).append(CUSTOM_HEADER_NAME);
  return std::filesystem::exists(path);
}
}  // namespace licenser::configmgr