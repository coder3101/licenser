/**
 * Copyright (C) 2019 Ashar ashar786khan@gmail.com
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

#include "LicenseWriter.hpp"
#include <exception>
#include <iostream>

namespace licenser {
LicenseWriter::LicenseWriter(std::unique_ptr<licenses::License> t,
                             std::string name)
    : name(name) {
  this->type = std::move(t);
  auto path = std::filesystem::path(cwd());
  path.append(name);
  this->stream = std::ofstream(path.string());
  if (!this->stream.is_open())
    throw std::runtime_error(
        "Failed to create " + name +
        " File. Do you have write permission in current working directory?");
}

std::string LicenseWriter::get_name() const noexcept { return this->name; }

void LicenseWriter::write() {
  // Todo Pass the type to preprocessor before writing here
  this->stream << type->body_to_string();
}

std::string LicenseWriter::cwd() const {
  return std::filesystem::current_path().string();
}

LicenseWriter::~LicenseWriter() {
  if (this->stream.is_open()) stream.close();
}
}  // namespace licenser