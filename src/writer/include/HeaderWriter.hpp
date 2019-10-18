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
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "License.hpp"
#include "CommandLineArgs.hpp"

namespace licenser::writer {
class HeaderWriter {
  HeaderWriter(std::vector<std::string> const &);
  HeaderWriter(const HeaderWriter&) = delete;
  HeaderWriter& operator=(const HeaderWriter&) = delete;
  bool write(licenser::ApplicationArgs const&);
  std::string get_file() const noexcept;
  ~HeaderWriter();
};
}  // namespace licenser::writer