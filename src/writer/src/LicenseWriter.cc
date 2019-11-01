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


#include "LicenseWriter.hpp"
#include <exception>
#include "PreProcessor.hpp"

namespace licenser::writer {
LicenseWriter::LicenseWriter(std::string name, std::string pth)
    : name(name) {
  auto path = std::filesystem::path(pth);
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

LicenseWriter::~LicenseWriter() {
  if (this->stream.is_open()) stream.close();
}
}  // namespace licenser
