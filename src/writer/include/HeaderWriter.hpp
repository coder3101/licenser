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
  bool write(licenser::ApplicationArgs const&, std::string, bool);

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
