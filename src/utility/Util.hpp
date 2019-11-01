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
#include <chrono>
#include <filesystem>
#include <string>
#include <iostream>
#include "ConfigWriter.hpp"

#include "License.hpp"
namespace licenser {
namespace lambdas {
auto is_valid_email = [](std::string s) {
  if (s.empty()) return true;
  //Todo (coder3101): check for multiple comma separated email also.
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
auto is_exist = [](std::string const &s) {
  // std::cout<<"checking "<<s<<"\n";
  std::filesystem::path p(s);
  return std::filesystem::exists(p) && std::filesystem::is_directory(p);
};
}  // namespace lambdas

unsigned int this_year() {
  auto cur_time = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
  auto tm_ptr = std::localtime(&time);
  return tm_ptr->tm_year + 1900;
}
}  // namespace licenser
