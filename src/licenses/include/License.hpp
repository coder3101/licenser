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