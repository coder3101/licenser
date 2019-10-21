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
#include <fstream>
#include <string>
#include <vector>

#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "PathUtility.hpp"
#define IGNORE_FILE_NAME ".licenserignore"

// Todo: Maybe make this into a way such that not only we ignore
// directory but also we do not open such directory at first place.

namespace licenser::configmgr {
class IgnoreReader {
 public:
  IgnoreReader(std::string path);

  IgnoreReader(const IgnoreReader&);

  bool should_ignore(std::string path_name);

  static bool exists(std::string directory);

 private:
  std::string root_path;
  std::vector<std::string> ignore_file;
  std::vector<std::string> ignore_directory;
  std::vector<std::string> ignore_extension;
 
};
}  // namespace licenser::configmgr
