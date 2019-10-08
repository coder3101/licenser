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

#include "ConfigParser.hpp"
namespace licenser::configmgr {
ConfigParser::ConfigParser(std::ifstream &in) : stream(in){};

licenser::ApplicationArgs ConfigParser::get_application_args() {
  this->read(
      [&](std::string line) {
        auto p = split(line);
        this->append_to_arg(p.first, p.second, this->args);
      },
      *this);
  return args;
}

std::vector<std::pair<std::string, std::string>>
ConfigParser::get_all_key_values() {
  std::vector<std::pair<std::string, std::string>> ret_val;
  this->read([&ret_val,
              this](std::string line) { ret_val.push_back(this->split(line)); },
             *this);
  return ret_val;
}

void ConfigParser::read(std::function<void(std::string const &)> func,
                        ConfigParser &parser) {
  parser.stream.seekg(0, std::ios::beg);
  std::string line;
  while (std::getline(parser.stream, line)) {
    if (line.empty() || starts_with(line, '#')) continue;
    line = trim_end(trim_start(line));
    func(line);
  }
}

bool ConfigParser::starts_with(std::string s, char c) {
  auto i = 0u;
  while (s[i] == ' ') i++;
  return s[i] == c;
}

std::string ConfigParser::trim_start(std::string s) {
  auto i = 0u;
  while (s[i] == ' ') i++;
  return s.substr(i, std::string::npos);
}

std::string ConfigParser::trim_end(std::string s) {
  if(s.empty()) return s;
  auto i = s.size() - 1;
  while (i >= 0 && (s[i] == ' ' || s[i] == '\n')) i--;
  std::string extra = s[s.size() - 1] == '\n' ? "\n" : "";
  return s.substr(0, i + 1) + extra;
}

std::pair<std::string, std::string> ConfigParser::split(std::string line) {
  std::pair<std::string, std::string> rv;
  auto ret = line.find('=');
  if (ret == std::string::npos) return rv;
  rv.first = trim_start(trim_end(line.substr(0, ret)));
  rv.second = trim_start(trim_end(line.substr(ret + 1, std::string::npos)));
  return rv;
}

bool ConfigParser::append_to_arg(std::string k, std::string v,
                                 licenser::ApplicationArgs &args) {
  if (k == "author")
    args.author = v;
  else if (k == "email")
    args.email = v;
  else if (k == "year")
    args.year = std::stoi(v);
  else if (k == "project")
    args.project = v;
  else if (k == "license")
    args.license = v;
  else if (k == "ongoing_project")
    args.ongoing_project = v == "true";
  else
    return false;
  return true;
}

}  // namespace licenser::configmgr
