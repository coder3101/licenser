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
  LicenseWriter(std::string name = "LICENSE");

  LicenseWriter(const LicenseWriter&) = delete;

  LicenseWriter& operator=(const LicenseWriter&) = delete;

  void write(ApplicationArgs const&);

  std::string cwd() const;

  std::string get_name() const noexcept;

  ~LicenseWriter();

 private:
  std::string name;
  std::ofstream stream;
};
}  // namespace licenser
