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

#include "ConfigWriter.hpp"
#include <filesystem>
#include <fstream>
namespace licenser::configmgr {
bool ConfigWriter::write(ApplicationArgs app, std::string path) {
  std::filesystem::path p(path);
  p.append(LICENSER_CONFIG_NAME);
  path = p.string();
  std::ofstream stream(path);
  if (!stream.is_open() || !stream.good()) return false;
  stream.seekp(0, std::ios_base::beg);
  stream << "author=" << app.author << '\n';
  stream << "email=" << app.email << '\n';
  stream << "license=" << app.license << '\n';
  stream << "ongoing_project=" << (app.ongoing_project ? "true" : "false")
         << '\n';
  stream << "project=" << app.project << '\n';
  stream << "year=" << app.year << '\n';
  stream.close();
  return true;
}
}  // namespace licenser::configmgr