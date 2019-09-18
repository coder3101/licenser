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
#include <string>
#include "LicenseType.hpp"

namespace licenser::licenses {
class License {
 public:
  License(LicenseType t);
  virtual inline std::string body_to_string() const = 0;

  virtual inline std::string header_to_string() const = 0;

  inline LicenseType enum_type() const noexcept;

  inline std::string license_name() const noexcept;

 protected:
  LicenseType typeLicense;
};
}  // namespace licenser::licenses