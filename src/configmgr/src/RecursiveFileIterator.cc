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


#include "RecursiveFileIterator.hpp"

#include <iostream>

namespace licenser::configmgr {
RecursiveFileIterator::RecursiveFileIterator(ConfigReader &reader)
    : reader(reader), manager(reader) {}
std::size_t RecursiveFileIterator::iterate(
    std::function<void(std::string file_path,
                       licenser::ApplicationArgs const &)>
        on_touched) {
  std::size_t touch_count = 0;
  auto Path = std::filesystem::path(reader.root_path());
  auto end = std::filesystem::recursive_directory_iterator();
  auto fiterator = std::filesystem::recursive_directory_iterator(Path);
  int last_depth = fiterator.depth();

  while (fiterator != end) {
    while (last_depth > fiterator.depth()) {
      manager.leave_dir();
      last_depth--;
    }
    if (fiterator->is_directory()) {
      manager.enter_dir(fiterator->path().string());
      last_depth = fiterator.depth();
      fiterator++;
      continue;
    }
    if (fiterator->is_regular_file()) {
      auto maybe_ignore = manager.get_ignore();
      auto maybe_touch = manager.get_only();

      if (maybe_touch.has_value()) {
        if (maybe_touch.value().should_touch(fiterator->path().string())) {
          if (maybe_ignore.has_value() &&
              maybe_ignore->should_ignore(
                  fiterator->path().string())) { /* Nothing Doing */
          } else {
            touch_count++;
            on_touched(fiterator->path().string(), manager.get_config().get());
          }
        }
      }

      else if (maybe_ignore.has_value()) {
        if (!maybe_ignore.value().should_ignore(fiterator->path().string())) {
          touch_count++;
          on_touched(fiterator->path().string(), manager.get_config().get());
        }
      } 
      
      else {
        on_touched(fiterator->path().string(), manager.get_config().get());
        touch_count++;
      }
      
      last_depth = fiterator.depth();
    }
    fiterator++;
  }
  return touch_count;
}
}  // namespace licenser::configmgr
