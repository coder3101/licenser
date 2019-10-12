/**
 * Copyright (C) 2019 Ashar ashar786khan@gmail.com
 *
 * This file is part of licenser.
 *
 * licenser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * licenser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with licenser.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ConfigIgnore.hpp"

#include <iostream>
#include <cstdlib>
namespace licenser::configmgr {
IgnoreReader::IgnoreReader(std::string path) : root_path(path) {
  stream = std::ifstream(
      std::filesystem::path(root_path).append(IGNORE_FILE_NAME).string());

  if (stream.is_open() && stream.good()) {
    std::string line;
    while (std::getline(stream, line)) {
      auto trimmed = ConfigParser::trim_end(ConfigParser::trim_start(line));
      if (trimmed.empty() || trimmed == "." || trimmed == ".." ||
          trimmed[0] == '#')
        continue;
      else {
        // Maybe extension filter is here
        if (trimmed[0] == '*' && trimmed[1] == '.')
          ignore_extension.push_back(trimmed.substr(1));

        // Maybe directory is here
        else if (trimmed[trimmed.size() - 1] == '/') {
          trimmed = trimmed.substr(0, trimmed.size() - 1) +
          #ifdef _WIN32
                  '\\';
          #else
                 std::filesystem::path::preferred_separator;
          #endif
          ignore_directory.push_back(trimmed);
        }

        // Everything else is exact file name
        else
          ignore_file.push_back(trimmed);
      }
    }
  } else if (stream.is_open())
    stream.close();
}

IgnoreReader::IgnoreReader(const IgnoreReader& copy) {
  this->ignore_directory = copy.ignore_directory;
  this->ignore_extension = copy.ignore_extension;
  this->ignore_file = copy.ignore_file;
  this->root_path = copy.root_path;
}

bool IgnoreReader::should_ignore(std::string path_name) {
  if (path_to_file_name(path_name) == LICENSER_CONFIG_NAME ||
      path_to_file_name(path_name) == IGNORE_FILE_NAME)
    return true;
  else {
    // Check for direct files
    for (auto e : ignore_file)
      if (e == path_to_file_name(path_name)) return true;

    // Check for extensions
    for (auto e : ignore_extension)
      if (e == path_to_extension_name(path_name)) return true;

    // Check for inside directory
    for (auto e : ignore_directory)
      if (path_inside_directory(path_name, e)) return true;

    return false;
  }
}

std::string IgnoreReader::path_to_file_name(std::string p) {
  return std::filesystem::path(p).filename().string();
}
std::string IgnoreReader::path_to_extension_name(std::string p) {
  return std::filesystem::path(p).extension().string();
}
bool IgnoreReader::path_inside_directory(std::string path,
                                         std::string directory) {
  return path.find(directory) != std::string::npos;
}

bool IgnoreReader::has_ignore_file(std::string path) {
  auto f = std::filesystem::path(path).append(IGNORE_FILE_NAME);
  return std::filesystem::exists(f);
}

}  // namespace licenser::configmgr