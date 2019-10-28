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

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "CommandLineArgs.hpp"
#include "Extensions.hpp"
#include "License.hpp"

namespace licenser::writer {
class HeaderRemover {
 public:
  static std::string from_str(std::string const& old, std::string extension) {
    std::string ans;
    std::size_t idx = 0;
    while (idx != old.size() && (old[idx] == ' ' || old[idx] == '\n')) idx++;

    auto commenter = licenser::comments::Extensions::to_lang(extension);

    bool is_multi_line = is_match(old, idx, commenter->multiline_begin());
    bool is_single_line = is_match(old, idx, commenter->singleline_begin());

    if (is_single_line) {
      std::size_t last_perfect_slice = idx;
      while (is_match(old, idx, commenter->singleline_begin())) {
        while (old[idx] != '\n' && idx != old.size()) idx++;
        idx++;
        //last_perfect_slice = idx;
        while (idx != old.size() && old[idx] == ' ') idx++;
      }
      while (idx < old.size() && (old[idx] == '\n' || old[idx] == ' ')) idx++;
      for (int t = idx /*last_perfect_slice*/; t < old.size(); t++) ans += old[t];
    } else if (is_multi_line) {
      idx += commenter->multiline_begin().size();
      while (idx < old.size() &&
             !is_match(old, idx, commenter->multiline_end()))
        idx++;
      idx += commenter->multiline_end().size();
      while (idx < old.size() && (old[idx] == '\n' || old[idx] == ' ')) idx++;
      for (int t = idx; t < old.size(); t++) ans += old[t];
    } else {
      return old;
    }
    return ans;
  }

 private:
  static bool is_match(std::string const& data, std::size_t idx,
                       std::string text) {
    for (int t = 0; t < text.size(); t++)
      if ((data.size() <= idx + t) || data[idx + t] != text[t]) {
        return false;
      }
    return true;
  }
};
}  // namespace licenser::writer
