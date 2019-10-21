/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
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


#include "ConfigManager.hpp"

namespace licenser::configmgr {
ConfigManager::ConfigManager(ConfigReader initial) {
  reader_stack.push(initial);

  if (IgnoreReader::exists(initial.root_path()))
    ignore_stack.push(initial.root_path());
  if (OnlyReader::exists(initial.root_path()))
    only_stack.push(initial.root_path());
}

void ConfigManager::enter_dir(std::string dir) {
  bool has_ignore = IgnoreReader::exists(dir);
  bool has_only = OnlyReader::exists(dir);
  bool has_config = ConfigReader::exists(dir);

  if (has_ignore)
    ignore_stack.push(dir);
  else if (!ignore_stack.empty())
    ignore_stack.push(ignore_stack.top());

  if (has_only)
    only_stack.push(dir);
  else if (!only_stack.empty())
    only_stack.push(only_stack.top());

  if (has_config)
    reader_stack.push(dir);
  else
    reader_stack.push(reader_stack.top());
}

void ConfigManager::leave_dir() {
  if (!ignore_stack.empty()) ignore_stack.pop();
  if (!only_stack.empty()) only_stack.pop();
  if (!reader_stack.empty()) reader_stack.pop();
}

ConfigReader ConfigManager::get_config() const {
  if (reader_stack.empty())
    throw std::runtime_error("Unexpected Error : Reader stack was empty");
  else
    return reader_stack.top();
}

std::optional<IgnoreReader> ConfigManager::get_ignore() const noexcept {
  std::optional<IgnoreReader> ret;
  if (!ignore_stack.empty()) ret = ignore_stack.top();
  return ret;
}

std::optional<OnlyReader> ConfigManager::get_only() const noexcept {
  std::optional<OnlyReader> ret;
  if (!only_stack.empty()) ret = only_stack.top();
  return ret;
}

}  // namespace licenser::configmgr
