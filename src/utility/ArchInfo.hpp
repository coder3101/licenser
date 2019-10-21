/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
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
