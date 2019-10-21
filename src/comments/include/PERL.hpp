/*
* Copyright (C) 2019- Mohammad Ashar Khan ashar786khan@gmail.com
*  
* This file is part of Licenser.
*  
* Licenser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*  
* Licenser is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*  
* You should have received a copy of the GNU General Public License
* along with Licenser.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include "Base.hpp"
namespace licenser::comments {
class Perl final : public CommentBase {
 public:
  std::string singleline_begin() override { return "#"; }
  char multiline_decorator() override { return DEFAULT_DECORATOR_ASTRICK; }
  std::string multiline_begin() override { return "="; }
  std::string multiline_end() override { return "=cut"; }
  bool has_multiline() override { return true; }
};
}  // namespace licenser::comments
