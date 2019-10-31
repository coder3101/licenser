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


#include "ConfigCommand.hpp"

namespace licenser::configmgr {
std::string CommandRunner::exec(std::string cmd) {
#if defined(_WIN32)
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"),
                                                 _pclose);
  if (!pipe) {
    throw std::runtime_error("_popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

#else
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("_popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

#endif
  std::string first_p;
  bool state = true;
  for (auto e : result)
    if (state && (e == '\n' || e == ' '))
      continue;
    else
      first_p += e, state = false;

  state = true;
  std::string rev_;
  for (int t = first_p.size() - 1; t >= 0; t--) {
    auto e = first_p[t];
    if (state && (e == '\n' || e == ' '))
      continue;
    else
      rev_ += e, state = false;
  }
  std::reverse(rev_.begin(), rev_.end());
  return rev_;
}
}  // namespace licenser::configmgr
