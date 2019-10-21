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

#define NULL_CHAR '\0'
#define DEFAULT_DECORATOR_ASTRICK '*'
#define DEFAULT_DECORATOR_POUND '#'
namespace licenser::comments {
class CommentBase {
 public:
  virtual std::string singleline_begin() = 0;
  virtual char multiline_decorator() = 0;
  virtual std::string multiline_begin() = 0;
  virtual std::string multiline_end() = 0;
  virtual bool has_multiline() = 0;
  virtual ~CommentBase() = default;
};
}  // namespace licenser::comments
