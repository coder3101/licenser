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
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "License.hpp"
#include "CommandLineArgs.hpp"

namespace licenser::writer {
class HeaderWriter {
  public:
  HeaderWriter(std::string path);
  HeaderWriter(const HeaderWriter&) = delete;
  HeaderWriter& operator=(const HeaderWriter&) = delete;
  bool write(licenser::ApplicationArgs const&, bool);

  std::string get_error_cause() const noexcept;
  ~HeaderWriter();
  private:
  std::string old_path;
  std::string new_temp_path;
  std::ofstream new_writer;
  std::ifstream old_reader;
  std::string error_cause;
};
}  // namespace licenser::writer
