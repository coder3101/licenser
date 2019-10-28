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
#include <fstream>
#include <string>
#define CUSTOM_HEADER_NAME ".header"

namespace licenser::configmgr {
class CustomHeader {
 public:
  static std::string read(std::string dir);
  static bool exists(std::string p);
};
}  // namespace licenser::configmgr
