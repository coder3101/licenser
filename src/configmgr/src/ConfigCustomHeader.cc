/*
* Copyright (c) 2019 Mohammad Ashar Khan <ashar786khan@gmail.com>
* 
* Licenser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Enjoy the software but don't blame me if you blow up things !!
* 
*/


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
