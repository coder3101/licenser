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

#include "RecursiveFileIterator.hpp"

namespace licenser::configmgr {
RecursiveFileIterator::RecursiveFileIterator(ConfigReader &reader)
    : reader(reader) {}
std::size_t RecursiveFileIterator::iterate(
    std::function<void(std::string file_path,
                       licenser::ApplicationArgs const &)>
        on_touched) {
  std::size_t touch_count = 0;
  auto Path = std::filesystem::path(reader.root_path());
  auto end = std::filesystem::recursive_directory_iterator();
  auto fiterator = std::filesystem::recursive_directory_iterator(Path);
  int last_depth = fiterator.depth();
  ignoreStack.push(reader.root_path());

  while (fiterator != end) {
    while (last_depth > fiterator.depth()) {
      reader.leave_dir();
      ignoreStack.pop();
      last_depth--;
    }
    if (fiterator->is_directory()) {
      if (IgnoreReader::has_ignore_file(fiterator->path().string()))
        ignoreStack.push(fiterator->path().string());
      else
        ignoreStack.push(ignoreStack.top());
      reader.enter_dir(fiterator->path().string());
      last_depth = fiterator.depth();
      fiterator++;
      continue;
    }
    if (fiterator->is_regular_file()) {
      if (!ignoreStack.top().should_ignore(fiterator->path().string())) {
        touch_count++;
        on_touched(fiterator->path().string(), reader.get());
      }
      last_depth = fiterator.depth();
    }
    fiterator++;
  }
  return touch_count;
}
}  // namespace licenser::configmgr