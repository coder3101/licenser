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


#pragma once

#include <filesystem>
#include <string>

namespace licenser {
struct PathUtility {
  static std::string path_to_filename(std::string path) {
    return std::filesystem::path(path).filename().string();
  }

  static std::string path_to_extension_name(std::string p) {
    return std::filesystem::path(p).extension().string();
  }
  static bool path_inside_directory(std::string path, std::string directory) {
    return path.find(directory) != std::string::npos;
  }
};
}  // namespace licenser
