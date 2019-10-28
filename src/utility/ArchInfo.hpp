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
#include <string>
namespace licenser {
std::string get_arch() {
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64) || \
    defined(__x86_64__) || defined(_M_AMD64)
  return "AMD64 (x86_64)";
#elif defined(__aarch64__)
  return "ARM64";
#elif defined(__arm__) || defined(_M_ARM)
  return "ARM"
#elif defined(_X86_) || defined(_M_IX86) || defined(_M_I86) || \
    defined(i386) || defined(__i386) || defined(__i386__)
  return "Intel x86";
#elif defined(__mips__) || defined(mips)
  return "MIPS";
#elif defined(__powerpc) || defined(__powerpc__)
  return "PowerPC";
#else
  return "Unknown";
#endif
}
}  // namespace licenser
