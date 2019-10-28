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

#include <memory>
#include <string>
#include "LicenseType.hpp"

namespace licenser::licenses {
class License {
 public:
  License(LicenseType t);
  virtual std::string body_to_string() const = 0;

  virtual std::string header_to_string() const = 0;

  inline LicenseType enum_type() const noexcept;
  virtual std::string name() const = 0;

  static std::string name_from_enum(LicenseType type) noexcept;

  static LicenseType enum_from_name(std::string s) noexcept;

  static std::string short_name_from_enum(LicenseType type) noexcept;

  static std::unique_ptr<License> make_license(
      LicenseType type, std::unique_ptr<License> custom = nullptr);

  virtual ~License() = default;

 protected:
  LicenseType typeLicense;
};
}  // namespace licenser::licenses
