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
#include <memory>
#include <filesystem>
#include <utility>

#include "License.hpp"
#include "CommandLineArgs.hpp"
namespace licenser::writer {
class LicenseWriter {
 public:
  LicenseWriter(std::string name = "LICENSE", std::string = ".");

  LicenseWriter(const LicenseWriter&) = delete;

  LicenseWriter& operator=(const LicenseWriter&) = delete;

  void write(ApplicationArgs const&);

  std::string get_name() const noexcept;

  ~LicenseWriter();

 private:
  std::string name;
  std::ofstream stream;
};
}  // namespace licenser
