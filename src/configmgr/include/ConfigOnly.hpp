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

// Only reader gets priority over IgnoreReader
#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "path_utility.hpp"

#define ONLY_FILE_NAME ".licenseronly"

namespace licenser::configmgr {
class OnlyReader {
 public:
  OnlyReader(std::string);
  OnlyReader(const OnlyReader&);
  bool should_touch(std::string);

  std::string root_path() const noexcept;
  static bool exists(std::string dir);

 private:

 std::string path;
 std::vector<std::string> only_file;
 std::vector<std::string> only_directory;
 std::vector<std::string> only_extension;

};
}  // namespace licenser::configmgr