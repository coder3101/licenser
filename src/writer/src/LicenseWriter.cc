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


#include "LicenseWriter.hpp"
#include <exception>
#include "PreProcessor.hpp"

namespace licenser::writer {
LicenseWriter::LicenseWriter(std::string name)
    : name(name) {
  auto path = std::filesystem::path(cwd());
  path.append(name);
  this->stream = std::ofstream(path.string());
  if (!this->stream.is_open())
    throw std::runtime_error(
        "Failed to create " + name +
        " File. Do you have write permission in current working directory?");
}

std::string LicenseWriter::get_name() const noexcept { return this->name; }

void LicenseWriter::write(ApplicationArgs const& args) {
  auto license_enum = ::licenser::licenses::License::enum_from_name(args.license);
  auto license_ptr = ::licenser::licenses::License::make_license(license_enum);
  this->stream << Preprocessor::parse(license_ptr->body_to_string(), args);
}

std::string LicenseWriter::cwd() const {
  return std::filesystem::current_path().string();
}

LicenseWriter::~LicenseWriter() {
  if (this->stream.is_open()) stream.close();
}
}  // namespace licenser
