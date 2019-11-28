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


#include "RecursiveFileIterator.hpp"

#include <iostream>

namespace licenser::configmgr {
RecursiveFileIterator::RecursiveFileIterator(ConfigReader &reader)
    : reader(reader), manager(reader) {}
std::size_t RecursiveFileIterator::iterate(
    std::function<void(std::string file_path,
                       licenser::ApplicationArgs const &, std::string)>
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
            on_touched(fiterator->path().string(), manager.get_config().get(),
                       manager.get_custom_header());
          }
        }
      }

      else if (maybe_ignore.has_value()) {
        if (!maybe_ignore.value().should_ignore(fiterator->path().string())) {
          touch_count++;
          on_touched(fiterator->path().string(), manager.get_config().get(),
                     manager.get_custom_header());
        }
      }

      else {
        on_touched(fiterator->path().string(), manager.get_config().get(),
                   manager.get_custom_header());
        touch_count++;
      }

      last_depth = fiterator.depth();
    }
    fiterator++;
  }
  return touch_count;
}

std::size_t RecursiveFileIterator::count(){
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
          }
        }
      }

      else if (maybe_ignore.has_value()) {
        if (!maybe_ignore.value().should_ignore(fiterator->path().string())) {
          touch_count++;
        }
      }

      else {
        touch_count++;
      }

      last_depth = fiterator.depth();
    }
    fiterator++;
  }
  reset();
  return touch_count;        
}

void RecursiveFileIterator::reset(){
	manager.reset();
}

}  // namespace licenser::configmgr
