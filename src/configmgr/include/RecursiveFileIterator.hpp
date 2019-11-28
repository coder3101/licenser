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
#include <functional>
#include <stack>

#include "ConfigManager.hpp"
namespace licenser::configmgr {
class RecursiveFileIterator {
 public:
  RecursiveFileIterator(ConfigReader &reader);

  std::size_t iterate(
      std::function<void(std::string path, licenser::ApplicationArgs const &, std::string)>);
  std::size_t count();

 private:
  ConfigReader &reader;
  ConfigManager manager;
  void reset();
};
}  // namespace licenser::configmgr
