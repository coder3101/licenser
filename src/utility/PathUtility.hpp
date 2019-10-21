/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
*  
* This file is part of Licenser.
*  
* Licenser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*  
* Licenser is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*  
* You should have received a copy of the GNU General Public License
* along with Licenser.  If not, see <http://www.gnu.org/licenses/>.
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
