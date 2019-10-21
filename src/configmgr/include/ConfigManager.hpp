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
#include <optional>
#include <stack>
#include <string>
#include <utility>

#include "CommandLineArgs.hpp"
#include "ConfigIgnore.hpp"
#include "ConfigOnly.hpp"
#include "ConfigReader.hpp"

namespace licenser::configmgr {
class ConfigManager {
 public:
  ConfigManager(ConfigReader);
  ConfigManager(const ConfigManager&) = delete;
  ConfigManager& operator=(const ConfigManager&) = delete;
  void enter_dir(std::string dir);
  void leave_dir();
  ConfigReader get_config() const;
  std::optional<IgnoreReader> get_ignore() const noexcept;
  std::optional<OnlyReader> get_only() const noexcept;

 private:
  std::stack<ConfigReader> reader_stack;
  std::stack<IgnoreReader> ignore_stack;
  std::stack<OnlyReader> only_stack;
};
}  // namespace licenser::configmgr
