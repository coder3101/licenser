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
#include "Base.hpp"
namespace licenser::comments {
class Kotlin final : public CommentBase {
 public:
  std::string singleline_begin() override { return "//"; }
  char multiline_decorator() override { return DEFAULT_DECORATOR_ASTRICK; }
  std::string multiline_begin() override { return "/*"; }
  std::string multiline_end() override { return "*/"; }
  bool has_multiline() override { return true; }
};
}  // namespace licenser::comments
