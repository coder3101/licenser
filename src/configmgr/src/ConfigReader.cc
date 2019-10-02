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

#include "ConfigReader.hpp"
#include <filesystem>
#include <fstream>

#include <iostream>

#ifndef LICENSER_CONFIG_NAME
#define LICENSER_CONFIG_NAME ".licenser.rc"
#endif
namespace licenser::configmgr {
ConfigReader::ConfigReader(std::string path) : root(path) {
  auto xf = ConfigReader::read(path);
  if (xf.has_value())
    this->root_config = xf.value();
  else
    throw std::runtime_error("The current path " + path +
                             "does not contain a licenser configuration file.");
  this->recursive_configs.push(this->root_config);
}

ApplicationArgs ConfigReader::get() const { return recursive_configs.top(); }

void ConfigReader::enter_dir(std::string new_path) {
  auto mxs = ConfigReader::read(new_path);
  if (mxs.has_value())
    this->recursive_configs.push(mxs.value());
  else
    this->recursive_configs.push(this->recursive_configs.top());
}

bool ConfigReader::leave_dir() {
  this->recursive_configs.pop();
  return !this->recursive_configs.empty();
}

std::optional<ApplicationArgs> ConfigReader::read(std::string path) {
  std::optional<ApplicationArgs> ret_val;

  std::filesystem::path p(path);
  p.append(LICENSER_CONFIG_NAME);
  path = p.string();

  std::ifstream config;
  config.open(path);
  if (config.is_open()) {
    std::string conf;
    while (std::getline(config, conf)) {
      if(conf.empty()) continue;
      std::cout<<conf<<"\n";
      // Make some string processing here
    }
  }
  return ret_val;
}

}  // namespace licenser::configmgr