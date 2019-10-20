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

#include <memory>

#include "Base.hpp"
#define COMMENT_CHAR_TEXT_SPACE " "
#define HEADER_SOURCE_LINE_BREAK "\n\n\n"

namespace licenser::comments {
struct CommentBuilder {
  static std::string from_header(std::unique_ptr<CommentBase> comment,
                                 std::string preprocessed,
                                 bool multiline = false) {
    std::string ans;
    if ((comment->has_multiline() && multiline) ||
        (comment->singleline_begin().size() == 0)) {
      // Use multiline as requested or when single line is no t possible
      ans += comment->multiline_begin();
      ans += '\n';
      ans += comment->multiline_decorator();
      ans += COMMENT_CHAR_TEXT_SPACE;
      for (auto e : preprocessed) {
        ans += e;
        if (e == '\n') {
          ans += comment->multiline_decorator();
          ans += COMMENT_CHAR_TEXT_SPACE;
        }
      }
      ans += '\n';
      ans += comment->multiline_end();
      ans += HEADER_SOURCE_LINE_BREAK;

    } else {
      // Use single line
      ans += comment->singleline_begin();
      ans += COMMENT_CHAR_TEXT_SPACE;
      for (auto e : preprocessed) {
        ans += e;
        if (e == '\n') {
          ans += comment->singleline_begin();
          ans += COMMENT_CHAR_TEXT_SPACE;
        }
      }
      ans += HEADER_SOURCE_LINE_BREAK;
    }
    return ans;
  }
};
}  // namespace licenser::comments