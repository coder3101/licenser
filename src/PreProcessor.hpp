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
#include <chrono>
#include <string>
#include "CommandLineArgs.hpp"
namespace licenser {
class Preprocessor {
 public:
  static std::string parse(std::string const &raw,
                           ApplicationArgs const &args) {
    int last_start = -1;
    std::string ans;
    for (int t = 0; t < raw.size(); t++) {
      if (last_start == -1 && raw[t] == '%')
        last_start = t;

      else if (raw[t] == '%') {
        std::string plh;
        for (int st = last_start + 1; st < t; st++) plh += raw[t];
        replace_placeholder(plh, ans, args);
        last_start = -1;
      } else if (last_start != -1) {
        if ((raw[t] >= 'A' && raw[t] <= 'Z') || raw[t] == '_')
          continue;
        else {
          std::string subpoint;
          for (int ts = last_start; ts <= t; ts++) subpoint += raw[ts];
          ans += subpoint;
          last_start = -1;
        }
      } else
        ans += raw[t];
    }
    return ans;
  }

 private:
  void static replace_placeholder(std::string placeholder_text,
                                  std::string &text,
                                  ApplicationArgs const &args) {
    if (placeholder_text == "AUTHOR")
      text += args.author;
    else if (placeholder_text == "EMAIL")
      text += args.email;
    else if (placeholder_text == "YEAR_FROM")
      text += args.year;
    else if (placeholder_text == "PROJECT")
      text += args.project;
    else if (placeholder_text == "YEAR_TO") {
      auto cur_time = std::chrono::system_clock::now();
      std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
      auto tm_ptr = std::localtime(&time);
      if (tm_ptr->tm_year + 1900 != args.year && args.ongoing_project)
        text += std::to_string(1900 + tm_ptr->tm_year);
    } else
      text += placeholder_text;
  }
};
}  // namespace licenser