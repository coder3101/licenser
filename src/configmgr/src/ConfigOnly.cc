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


#include "ConfigOnly.hpp"

#include "ConfigIgnore.hpp"

namespace licenser::configmgr {
OnlyReader::OnlyReader(std::string path) {
  auto stream = std::ifstream(
      std::filesystem::path(path).append(ONLY_FILE_NAME).string());

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
          only_extension.push_back(trimmed.substr(1));

        // Maybe directory is here
        else if (trimmed[trimmed.size() - 1] == '/') {
          trimmed = trimmed.substr(0, trimmed.size() - 1) +
#ifdef _WIN32
                    '\\';
#else
                    std::filesystem::path::preferred_separator;
#endif
          only_directory.push_back(trimmed);
        }

        // Everything else is exact file name
        else
          only_file.push_back(trimmed);
      }
    }
  } else if (stream.is_open())
    stream.close();
}

OnlyReader::OnlyReader(const OnlyReader& other) {
  this->only_directory = other.only_directory;
  this->only_extension = other.only_extension;
  this->only_file = other.only_file;
  this->path = other.path;
}
bool OnlyReader::should_touch(std::string path) {
  for (auto e : only_file)
    if (e == licenser::PathUtility::path_to_filename(path)) return true;

  for (auto e : only_extension)
    if (e == licenser::PathUtility::path_to_extension_name(path)) return true;

  for (auto e : only_directory)
    if (licenser::PathUtility::path_inside_directory(path, e)) return true;

  return false;
}
std::string OnlyReader::root_path() const noexcept { return path; }
bool OnlyReader::exists(std::string dir) {
  auto f = std::filesystem::path(dir).append(ONLY_FILE_NAME);
  return std::filesystem::exists(f);
}

}  // namespace licenser::configmgr
