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
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "CommandLineArgs.hpp"
namespace licenser::configmgr {
class ConfigParser {
 public:
  ConfigParser(std::ifstream& stream);
  ConfigParser() = delete;
  ConfigParser(ConfigParser&&) = delete;
  ConfigParser(ConfigParser&) = delete;

  ConfigParser& operator=(ConfigParser&) = delete;
  licenser::ApplicationArgs get_application_args();

  std::vector<std::pair<std::string, std::string>> get_all_key_values();

  static void read(std::function<void(std::string const&)>, ConfigParser &);
  static std::string trim_start(std::string s);

  static std::string trim_end(std::string s);

  static bool starts_with(std::string s, char c);

  static bool append_to_arg(std::string k, std::string v, licenser::ApplicationArgs &args);

  static std::pair<std::string, std::string> split(std::string line);

 private:
  std::ifstream& stream;
  licenser::ApplicationArgs args;
};
}  // namespace licenser::configmgr
