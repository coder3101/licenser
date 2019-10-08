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
#include <chrono>
#include <string>
#include "License.hpp"
namespace licenser {
namespace lambdas {
auto is_valid_email = [](std::string s) {
  if (s.empty()) return true;
  auto at_idx = s.find('@');
  auto last_dot = s.find_last_of('.');
  return at_idx != std::string::npos && last_dot != std::string::npos &&
         last_dot > at_idx;
};
auto is_valid_year = [](std::string s) {
  try {
    auto res = std::atoi(s.c_str());
    return res > 1900;
  } catch (...) {
    return false;
  }
};

auto is_valid_license = [](std::string s) {
  return licenser::licenses::License::enum_from_name(s) !=
         licenser::licenses::LicenseType::UNKNOWN;
};

auto is_non_empty = [](std::string s) { return !s.empty(); };
}  // namespace lamdas

unsigned int this_year() {
  auto cur_time = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
  auto tm_ptr = std::localtime(&time);
  return tm_ptr->tm_year + 1900;
}
}  // namespace licenser