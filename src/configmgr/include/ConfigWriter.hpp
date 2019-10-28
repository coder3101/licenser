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

#include "CommandLineArgs.hpp"

#ifndef LICENSER_CONFIG_NAME
#define LICENSER_CONFIG_NAME ".licenserrc"
#endif
namespace licenser::configmgr {
class ConfigWriter {
 public:
  static bool write(ApplicationArgs app, std::string path = ".");
};
}  // namespace licenser::configmgr
