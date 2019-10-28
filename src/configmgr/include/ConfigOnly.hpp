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


// Only reader gets priority over IgnoreReader
#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "PathUtility.hpp"

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
