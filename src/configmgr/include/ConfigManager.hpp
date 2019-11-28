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
#include <utility>

#include "CommandLineArgs.hpp"
#include "ConfigIgnore.hpp"
#include "ConfigOnly.hpp"
#include "ConfigReader.hpp"
#include "ConfigCustomHeader.hpp"

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
  std::string get_custom_header() const noexcept;
  void reset() noexcept;

 private:
  std::stack<ConfigReader> reader_stack;
  std::stack<IgnoreReader> ignore_stack;
  std::stack<OnlyReader> only_stack;
  std::stack<std::string> custom_header;
  ConfigReader initial; 
};
}  // namespace licenser::configmgr
