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


#include "ConfigReader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ConfigParser.hpp"

namespace licenser::configmgr {
ConfigReader::ConfigReader(std::string path) : root(path) {
  auto xf = ConfigReader::read(path);
  if (xf.has_value())
    this->root_config = xf.value();
  else
    throw std::runtime_error("The current path " + path +
                             "does not contain a licenser configuration file.");
}

ApplicationArgs ConfigReader::get() const {
  return root_config;
}

std::string ConfigReader::root_path() const { return this->root; }

std::optional<ApplicationArgs> ConfigReader::read(std::string path) {
  std::optional<ApplicationArgs> ret_val;

  std::filesystem::path p(path);
  p.append(LICENSER_CONFIG_NAME);
  path = p.string();

  std::ifstream config;
  config.open(path);
  if (config.is_open() && config.good()) {
    ConfigParser parser(config);
    ret_val = parser.get_application_args();
  }
  return ret_val;
}

bool ConfigReader::exists(std::string path) {
  auto f = std::filesystem::path(path).append(LICENSER_CONFIG_NAME);
  return std::filesystem::exists(f);
}

}  // namespace licenser::configmgr
