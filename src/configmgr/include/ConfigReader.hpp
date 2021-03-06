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
#include <optional>
#include <stack>
#include <string>
#include "CommandLineArgs.hpp"

#ifndef LICENSER_CONFIG_NAME
#define LICENSER_CONFIG_NAME ".licenserrc"
#endif

namespace licenser::configmgr {
class ConfigReader {
 public:
  ConfigReader(std::string path = ".");
  ApplicationArgs get() const;
  std::string root_path() const ;

  static std::optional<ApplicationArgs> read(std::string path = ".");
  static bool exists(std::string path = ".");

 private:
  std::string root;
  ApplicationArgs root_config;
};
}  // namespace licenser::configmgr
