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
#include <filesystem>
#include <functional>
#include <stack>

#include "ConfigIgnore.hpp"
#include "ConfigReader.hpp"
namespace licenser::configmgr {
class RecursiveFileIterator {
 public:
  RecursiveFileIterator(ConfigReader &reader);

  std::size_t iterate(
      std::function<void(std::string path, licenser::ApplicationArgs const &)>);

 private:
  ConfigReader &reader;
  std::stack<licenser::configmgr::IgnoreReader> ignoreStack;
};
}  // namespace licenser::configmgr