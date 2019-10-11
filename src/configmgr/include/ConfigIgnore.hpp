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

#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#define IGNORE_FILE_NAME ".licenserignore"

// Todo: Maybe make this into a way such that not only we ignore
// directory but also we do not open such directory at first place.

namespace licenser::configmgr {
class IgnoreReader {
 public:
  IgnoreReader(std::string path);

  IgnoreReader(const IgnoreReader&);

  bool should_ignore(std::string path_name);

  static bool has_ignore_file(std::string directory);

 private:
  std::string root_path;
  std::ifstream stream;
  std::vector<std::string> ignore_file;
  std::vector<std::string> ignore_directory;
  std::vector<std::string> ignore_extension;
  std::string path_to_file_name(std::string p);
  std::string path_to_extension_name(std::string p);
  bool path_inside_directory(std::string directory, std::string path);
};
}  // namespace licenser::configmgr